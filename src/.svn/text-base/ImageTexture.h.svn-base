#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

/**
 * \file ImageTexture.h
 * \brief Image texture creator
 * \author Quentin Grimaud, Michael Gygli, Valentin Michelet
 * \version 0.7
 * \date June 2011
 *
 * Program to create a texture from an image.
 *
 */
#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture {
public:
	Image *_image;	/*!<  */

	ImageTexture(std::string file_name);
	virtual ~ImageTexture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* IMAGETEXTURE_H_ */
