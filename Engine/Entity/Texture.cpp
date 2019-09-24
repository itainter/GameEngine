#include "Texture.h"

using namespace Engine;

Texture::Texture()
{
    m_pTexture.reset();
}

Texture::Texture(std::string uri) :
    m_uri(uri)
{
    m_pTexture.reset();
}

Texture::~Texture()
{
}

std::string Texture::GetURI() const
{
    return m_uri;
}

void Texture::SetURI(std::string uri)
{
    m_uri = uri;
}