#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <boost/serialization/split_free.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(sf::Vertex)

BOOST_SERIALIZATION_SPLIT_FREE(sf::VertexArray)


namespace boost::serialization {
    template<class Archive>
    void serialize(Archive &ar, sf::Vector2f &vec, const unsigned int) {
        ar & vec.x & vec.y;
    }

    template<class Archive>
    void serialize(Archive &ar, sf::Color &color, const unsigned int) {
        ar & color.r & color.g & color.b & color.a;
    }

    template<class Archive>
    void save(Archive &ar, const sf::Vertex &v, const unsigned int) {
        ar << v.position << v.color << v.texCoords;
    }

    template<class Archive>
    void load(Archive &ar, sf::Vertex &v, const unsigned int) {
        ar >> v.position >> v.color >> v.texCoords;
    }

    template<class Archive>
    void save(Archive &ar, const sf::VertexArray &va, const unsigned int) {
        auto type = static_cast<int>(va.getPrimitiveType());
        ar << type << va.getVertexCount();
        for (size_t i = 0; i < va.getVertexCount(); ++i)
            ar << va[i];
    }

    template<class Archive>
    void load(Archive &ar, sf::VertexArray &va, const unsigned int) {
        int type;
        size_t count;
        ar >> type >> count;

        va.setPrimitiveType(static_cast<sf::PrimitiveType>(type));
        va.resize(count);

        for (size_t i = 0; i < count; ++i)
            ar >> va[i];
    }
}
