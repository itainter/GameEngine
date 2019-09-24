#include "GLTF2Loader.h"

#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#include "TransformComponent.h"
#include "MeshFilterComponent.h"
#include "MeshRendererComponent.h"

using namespace Engine;

GLTF2Loader::GLTF2Loader()
{
}

GLTF2Loader::~GLTF2Loader()
{
}

void GLTF2Loader::Load(std::string filename)
{
    m_pMeshes.clear();
    m_pMaterials.clear();

    m_asset = gltf2::load(filename);

    LoadMaterials();
    LoadMeshes();
}

void GLTF2Loader::ApplyToWorld()
{
    auto& pWorld = gpGlobal->GetECSWorld();

    auto nodes = m_asset.nodes;
    auto meshes = m_asset.meshes;

    std::for_each(nodes.begin(), nodes.end(), [&](gltf2::Node& aNode){
        auto mesh = meshes[aNode.mesh];

        //auto pMaterial = m_pMaterials[meshes[mesh.primitives[0].material]];
        auto pMesh = m_pMeshes[aNode.mesh];

        TransformComponent transformComp;
        MeshFilterComponent meshFilterComp;
        MeshRendererComponent meshRendererComp;

        meshFilterComp.SetMesh(std::shared_ptr<IMesh>(pMesh));
        //meshRendererComp.SetMaterial(std::shared_ptr<IMaterial>(pMaterial));

        pWorld->CreateEntity<TransformComponent, MeshFilterComponent, MeshRendererComponent>(transformComp, meshFilterComp, meshRendererComp);
    });
}

void GLTF2Loader::LoadMaterials()
{
    auto materials = m_asset.materials;
    auto textures = m_asset.textures;
    auto images = m_asset.images;

    std::for_each(materials.begin(), materials.end(), [&](gltf2::Material& aMaterial){
        float4 baseColor = aMaterial.pbr.baseColorFactor;
        auto baseColorTexture = images[textures[aMaterial.pbr.baseColorTexture.index].source].uri;
        auto normalTexture = images[textures[aMaterial.normalTexture.index].source].uri;

        auto metallic = aMaterial.pbr.metallicFactor;
        auto roughness = aMaterial.pbr.roughnessFactor;
        auto metallicRoughnessTexture = images[textures[aMaterial.pbr.metallicRoughnessTexture.index].source].uri;
        auto occlusionTexture = images[textures[aMaterial.occlusionTexture.index].source].uri;

        IMaterial* pMaterial = new Material();

        pMaterial->SetAlbedoColor(baseColor);
        pMaterial->SetAlbedoMap(std::shared_ptr<ITexture>(new Texture(baseColorTexture)));
        pMaterial->SetNormalMap(std::shared_ptr<ITexture>(new Texture(normalTexture)));

        pMaterial->SetMetallic(metallic);
        pMaterial->SetRoughness(roughness);
        pMaterial->SetMetallicRoughnessMap(std::shared_ptr<ITexture>(new Texture(metallicRoughnessTexture)));
        pMaterial->SetOcclusionMap(std::shared_ptr<ITexture>(new Texture(occlusionTexture)));

        m_pMaterials.push_back(pMaterial);
    });
}

void GLTF2Loader::LoadMeshes()
{
    auto meshes = m_asset.meshes;
    auto buffers = m_asset.buffers;
    auto accessors = m_asset.accessors;
    auto bufferViews = m_asset.bufferViews;

    std::for_each(meshes.begin(), meshes.end(), [&](gltf2::Mesh& aMesh){
        auto primitives = aMesh.primitives;
        std::for_each(primitives.begin(), primitives.end(), [&](gltf2::Primitive& aPrimitive){
            IMesh* pMesh = new Mesh();
            auto attributes = aPrimitive.attributes;
            std::for_each(attributes.begin(), attributes.end(), [&](gltf2::Attributes::value_type& aAttribute){
                auto str = aAttribute.first;
                auto num = aAttribute.second;

                Attribute::ESemanticType type;
                if (str ==  "POSITION")
                    type = Attribute::ESemanticType::Position;
                else if (str == "NORMAL")
                    type = Attribute::ESemanticType::Normal;
                else if (str == "TEXCOORD_0")
                    type = Attribute::ESemanticType::Texcoord0;
                else
                    return;

                int bufferView = accessors[num].bufferView;
                int count = accessors[num].count;

                int offset = bufferViews[bufferView].byteOffset;
                int subsize = bufferViews[bufferView].byteLength;

                auto pData = buffers[bufferViews[bufferView].buffer].data;
                char* data = new char[subsize];
                memcpy(data, pData + offset, subsize);

                pMesh->AttachVertexData(data, subsize, count, type, Attribute::EFormatType::Float3, str);
            });

            auto indexNum = aPrimitive.indices;

            int bufferView = accessors[indexNum].bufferView;
            int count = accessors[indexNum].count;

            int offset = bufferViews[bufferView].byteOffset;
            int subsize = bufferViews[bufferView].byteLength;

            auto pData = buffers[bufferViews[bufferView].buffer].data;
            char* data = new char[subsize];
            memcpy(data, pData + offset, subsize);

            pMesh->AttachIndexData(data, subsize, count);

            m_pMeshes.push_back(pMesh);
        });
    });
}