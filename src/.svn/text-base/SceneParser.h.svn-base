#ifndef SCENEPARSER_H_
#define SCENEPARSER_H_

/**
 * \file SceneParser.h
 * \brief XML file parser
 * \author Michelet Valentin
 * \version 0.7
 * \date June 2011
 *
 * Parse scene description XML files.
 * From a well written scene XML file, every shape, light source and screen option are initialized.
 * To write such a file, please see the tutorial "How to describe a scene".
 */
#include <string>

#include "tinyxml.h"

#include "Cylindre.h"
#include "Draughtboard.h"
#include "ImageTexture.h"
#include "LightSource.h"
#include "MarbleTexture.h"
#include "NoiseTexture.h"
#include "Plane.h"
#include "Quadrics.h"
#include "Rectangle.h"
#include "ScreenV2.h"
#include "Set.h"
#include "ScreenV2.h"
#include "Shape.h"
#include "Sphere.h"
#include "Texture.h"
#include "UVSphere.h"

/**
 * \class SceneParser
 * \brief XML file parser class
 *
 * Class to parse scene description XML files.
 */
class SceneParser {
public:
	char* _fileName;
	Set<Shape*> _shapes;
	Set<LightSource*> _lightSources;
	int _screenWidth, _screenHeight, _oversampling;
	ScreenV2 _camera;

	/**
	 * \brief Constructor
	 *
	 * Construct the parser from a XML file
	 */
	SceneParser(char* fileName = (char*)"./SceneDescriptions/defaultScene.xml");

	/**
	 * \brief Destructor
	 *
	 * Destruct the parser
	 */
	virtual ~SceneParser();

	/**
	 * \brief general parser
	 *
	 * Parse the XML file specified by the class instance _fileName
	 */
	void parse();

	/**
	 * \brief screen setup
	 *
	 * Parse the XML file to set the screen options
	 *
	 * \param elem : the node that contains the screen options
	 */
	void screenSetup(TiXmlElement *elem);

	/**
	 * \brief shape parser
	 *
	 * Parse the XML file to set the different shapes
	 *
	 * \param elem : the node that contains the shapes
	 * \return a pointer on the new shape created
	 */
	Shape* parseShape(TiXmlElement *elem);

	/**
	 * \brief light parser
	 *
	 * Parse the XML file to set the different lights
	 *
	 * \param elem : the node that contains the lights
	 */
	void parseLight(TiXmlElement *elem);

	/**
	 * \brief texture parser
	 *
	 * Parse the XML file to get a texture
	 *
	 * \param elem : the node that contains the texture
	 * \return the texture parsing
	 */
	Texture* parseTexture(TiXmlElement *elem);

	/**
	 * \brief camera parser
	 *
	 * Parse the XML file to get the camera
	 *
	 * \param elem : the node that contains the camera
	 */
	void parseCamera(TiXmlElement *elem);

	/**
	 * \brief parsing info
	 *
	 * Summarize the parsing info results
	 */
	void parsingInfo();
};

#endif /* SCENEPARSER_H_ */
