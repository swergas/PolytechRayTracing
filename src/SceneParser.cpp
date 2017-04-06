#include "SceneParser.h"
#include "Timer.h"

SceneParser::SceneParser(char* fileName) :
	_fileName(fileName) {
	_screenHeight = 480;
	_screenWidth = 640;
	_oversampling = 1;
	parse();
}

SceneParser::~SceneParser() {
}

void SceneParser::parse() {
	nsUtil::Timer timer = nsUtil::Timer();
	TiXmlDocument scene(_fileName);
	if (!scene.LoadFile()) {
		cerr << "error while loading" << endl;
		cerr << "error #" << scene.ErrorId() << " : " << scene.ErrorDesc() << endl;
		exit(-1);
	} else {
		//Timer Start
		timer.start();

		TiXmlHandle hdl(&scene);
		TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
		if (!elem) {
			cerr << "The node to reach does not exist" << endl;
			exit(-1);
		}
		//Browse every node
		while (elem) {
			if ((std::string) elem->Value() == "screenSetup") {
				screenSetup(elem);
			} else if ((std::string) elem->Value() == "shape") {
				Shape *s = parseShape(elem);
				_shapes.add(s);
			} else if ((std::string) elem->Value() == "light") {
				parseLight(elem);
			} else if ((std::string) elem->Value() == "camera") {
				parseCamera(elem);
			} else {
				cerr << "Invalid description: " << (std::string) elem->Value() << " does not exist.\nPlease, check the spelling and try again." << endl;
				exit(-1);
			}
			elem = elem->NextSiblingElement();
		}
		int time = timer.getTicks();
		cout << "\nParsing time: " << time/1000.0 << "s\n" << endl;
		parsingInfo();
	}
}

void SceneParser::screenSetup(TiXmlElement *elem) {
	elem->QueryIntAttribute("width", &_screenWidth);
	elem->QueryIntAttribute("height", &_screenHeight);
	elem->QueryIntAttribute("overSampling", &_oversampling);
}

Shape* SceneParser::parseShape(TiXmlElement *elem) {
	std::string shapeType = elem->Attribute("type");
	Shape *s;
	Color color;
	Material material;
	elem->FirstChildElement("color")->QueryDoubleAttribute("r", &color[0]);
	elem->FirstChildElement("color")->QueryDoubleAttribute("g", &color[1]);
	elem->FirstChildElement("color")->QueryDoubleAttribute("b", &color[2]);
	elem->FirstChildElement("material")->QueryDoubleAttribute("ka", &material.k_a);
	elem->FirstChildElement("material")->QueryDoubleAttribute("kd", &material.k_d);
	elem->FirstChildElement("material")->QueryDoubleAttribute("ks", &material.k_s);
	elem->FirstChildElement("material")->QueryDoubleAttribute("ns", &material.n_s);
	elem->FirstChildElement("material")->QueryDoubleAttribute("kreflex", &material.k_reflex);
	if (shapeType == "quadric") {
		double a, b, c, d, e, f, g, h, i, j;
		elem->FirstChildElement("a")->QueryDoubleAttribute("value", &a);
		elem->FirstChildElement("b")->QueryDoubleAttribute("value", &b);
		elem->FirstChildElement("c")->QueryDoubleAttribute("value", &c);
		elem->FirstChildElement("d")->QueryDoubleAttribute("value", &d);
		elem->FirstChildElement("e")->QueryDoubleAttribute("value", &e);
		elem->FirstChildElement("f")->QueryDoubleAttribute("value", &f);
		elem->FirstChildElement("g")->QueryDoubleAttribute("value", &g);
		elem->FirstChildElement("h")->QueryDoubleAttribute("value", &h);
		elem->FirstChildElement("i")->QueryDoubleAttribute("value", &i);
		elem->FirstChildElement("j")->QueryDoubleAttribute("value", &j);
		s = new Quadrics(color, material, a, b, c, d, e, f, g, h, i, j);
	} else if (shapeType == "uvsphere" || shapeType == "sphere") {
		Vector3 center;
		double radius;
		elem->FirstChildElement("center")->QueryDoubleAttribute("x", &center[0]);
		elem->FirstChildElement("center")->QueryDoubleAttribute("y", &center[1]);
		elem->FirstChildElement("center")->QueryDoubleAttribute("z", &center[2]);
		elem->FirstChildElement("radius")->QueryDoubleAttribute("value", &radius);
		if (shapeType == "uvsphere") {
			Texture *texture;
			double plusPhi;
			double plusTheta;

			texture = parseTexture(elem);

			elem->FirstChildElement("plusphi")->QueryDoubleAttribute("value", &plusPhi);
			plusPhi *= M_PI;

			elem->FirstChildElement("plustheta")->QueryDoubleAttribute("value", &plusTheta);
			plusTheta *= M_PI;

			s = new UVSphere(color, material, center, radius, texture, plusTheta, plusPhi);
		} else if (shapeType == "sphere") {
			s = new Sphere(color, material, center, radius);
		}
	} else if (shapeType == "draughtboard" || shapeType == "rectangle" || shapeType == "plane") {
		Ray normAndPoint;
		elem->FirstChildElement("center")->QueryDoubleAttribute("x", &normAndPoint[0][0]);
		elem->FirstChildElement("center")->QueryDoubleAttribute("y", &normAndPoint[0][1]);
		elem->FirstChildElement("center")->QueryDoubleAttribute("z", &normAndPoint[0][2]);
		elem->FirstChildElement("normal")->QueryDoubleAttribute("x", &normAndPoint[1][0]);
		elem->FirstChildElement("normal")->QueryDoubleAttribute("y", &normAndPoint[1][1]);
		elem->FirstChildElement("normal")->QueryDoubleAttribute("z", &normAndPoint[1][2]);
		if (shapeType == "plane") {
			s = new Plane(color, material, normAndPoint);
		} else if (shapeType == "draughtboard" || shapeType == "rectangle") {
			double height;
			double width;
			elem->FirstChildElement("height")->QueryDoubleAttribute("value", &height);
			elem->FirstChildElement("width")->QueryDoubleAttribute("value", &width);
			if (shapeType == "rectangle") {
				s = new Rectangle(color, material, normAndPoint, height, width);
			} else if (shapeType == "draughtboard") {
				Color colorD;
				double caseSize;
				elem->FirstChildElement("otherColor")->QueryDoubleAttribute("r", &colorD[0]);
				elem->FirstChildElement("otherColor")->QueryDoubleAttribute("g", &colorD[1]);
				elem->FirstChildElement("otherColor")->QueryDoubleAttribute("b", &colorD[2]);
				elem->FirstChildElement("caseSize")->QueryDoubleAttribute("value", &caseSize);
				s = new Draughtboard(color, material, colorD, normAndPoint, height, width, caseSize);
			}
		}
	}/* else if (shapeType == "cylindre") {
		Vector3 origin;
		Vector3 height;
		double radius;
		elem->FirstChildElement("origin")->QueryDoubleAttribute("x", &origin[0]);
		elem->FirstChildElement("origin")->QueryDoubleAttribute("y", &origin[1]);
		elem->FirstChildElement("origin")->QueryDoubleAttribute("z", &origin[2]);
		elem->FirstChildElement("height")->QueryDoubleAttribute("x", &height[0]);
		elem->FirstChildElement("height")->QueryDoubleAttribute("y", &height[1]);
		elem->FirstChildElement("height")->QueryDoubleAttribute("z", &height[2]);
		elem->FirstChildElement("radius")->QueryDoubleAttribute("value", &radius);
		s = new Cylindre(color, material, origin, height, radius);
	}*/ else {
		cerr << "Invalid description: " << shapeType << " does not exist.\nPlease, check the spelling and try again." << endl;
		exit(-1);
	}
	cout << "  Shape #" << _shapes.size()+1 << " (" << shapeType.substr(0, 7) << ")" << "\t[OK]" << endl;
	return s;
}

Texture* SceneParser::parseTexture(TiXmlElement *elem) {
	Texture *texture;
	std::string textureType = elem->FirstChildElement("texture")->Attribute("type");
	if (textureType == "image") {
		texture = new ImageTexture((std::string)elem->FirstChildElement("texture")->FirstChildElement("src")->Attribute("value"));
	} else if (textureType == "marble") {
		Color c0;
		Color c1;
		Color c2;
		float stripes_per_unit;
		float scale;
		int octaves;
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("r", &c0[0]);
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("g", &c0[1]);
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("b", &c0[2]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("r", &c1[0]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("g", &c1[1]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("b", &c1[2]);
		elem->FirstChildElement("texture")->FirstChildElement("c2")->QueryDoubleAttribute("r", &c2[0]);
		elem->FirstChildElement("texture")->FirstChildElement("c2")->QueryDoubleAttribute("g", &c2[1]);
		elem->FirstChildElement("texture")->FirstChildElement("c2")->QueryDoubleAttribute("b", &c2[2]);
		elem->FirstChildElement("texture")->FirstChildElement("stripesPerUnit")->QueryFloatAttribute("value", &stripes_per_unit);
		elem->FirstChildElement("texture")->FirstChildElement("scale")->QueryFloatAttribute("value", &scale);
		elem->FirstChildElement("texture")->FirstChildElement("octaves")->QueryIntAttribute("value", &octaves);
		texture = new MarbleTexture(c0, c1, c2, stripes_per_unit, scale, octaves);
	} else if (textureType == "noise") {
		Color c0;
		Color c1;
		float scale;
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("r", &c0[0]);
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("g", &c0[1]);
		elem->FirstChildElement("texture")->FirstChildElement("c0")->QueryDoubleAttribute("b", &c0[2]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("r", &c1[0]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("g", &c1[1]);
		elem->FirstChildElement("texture")->FirstChildElement("c1")->QueryDoubleAttribute("b", &c1[2]);
		elem->FirstChildElement("texture")->FirstChildElement("scale")->QueryFloatAttribute("value", &scale);
		texture = new NoiseTexture(c0, c1, scale);
	} else {
		cerr << "Invalid description: " << textureType << " does not exist.\nPlease, check the spelling and try again." << endl;
		exit(-1);
	}
	return texture;
}

void SceneParser::parseLight(TiXmlElement *elem) {
	double intensity;
	Vector3 position;
	Color color;
	elem->FirstChildElement("intensity")->QueryDoubleAttribute("value", &intensity);
	elem->FirstChildElement("position")->QueryDoubleAttribute("x", &position[0]);
	elem->FirstChildElement("position")->QueryDoubleAttribute("y", &position[1]);
	elem->FirstChildElement("position")->QueryDoubleAttribute("z", &position[2]);
	elem->FirstChildElement("color")->QueryDoubleAttribute("r", &color[0]);
	elem->FirstChildElement("color")->QueryDoubleAttribute("g", &color[1]);
	elem->FirstChildElement("color")->QueryDoubleAttribute("b", &color[2]);
	LightSource *l = new LightSource(intensity, position, color);
	_lightSources.add(l);
	cout << "  Light #" << _lightSources.size() << "\t\t[OK]" << endl;
}

void SceneParser::parseCamera(TiXmlElement *elem) {
	Vector3 observer;
	Vector3 wayUp;
	Vector3 aimedPoint;
	double viewAngle;
	double distScreen;
	elem->FirstChildElement("observer")->QueryDoubleAttribute("x", &observer[0]);
	elem->FirstChildElement("observer")->QueryDoubleAttribute("y", &observer[1]);
	elem->FirstChildElement("observer")->QueryDoubleAttribute("z", &observer[2]);
	elem->FirstChildElement("aimedPoint")->QueryDoubleAttribute("x", &aimedPoint[0]);
	elem->FirstChildElement("aimedPoint")->QueryDoubleAttribute("y", &aimedPoint[1]);
	elem->FirstChildElement("aimedPoint")->QueryDoubleAttribute("z", &aimedPoint[2]);
	elem->FirstChildElement("viewAngle")->QueryDoubleAttribute("value", &viewAngle);
	elem->FirstChildElement("distScreen")->QueryDoubleAttribute("value", &distScreen);
	_camera = ScreenV2(observer, aimedPoint, M_PI*viewAngle, _screenWidth, _screenHeight);
	_camera.initFromDistScreen(distScreen);
}

void SceneParser::parsingInfo() {
	cout << "\n## Information:" << endl;
	cout << "" << endl;
	cout << "Screen settings:" << endl;
	cout << "  Width:\t\t" << _screenWidth << endl;
	cout << "  Height:\t\t" << _screenHeight << endl;
	cout << "  Over sampling:\t" << _oversampling << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Sene settings:" << endl;
	cout << "  Shapes used:\t\t" << _shapes.length() << endl;
	cout << "  Lights used:\t\t" << _lightSources.length() << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Camera settings:" << endl;
	cout << "  Camera Rayon:\t\t" << (_camera._observer - _camera._aimedPoint).norm() << endl;
	cout << "  Initialized:\t\t" << _camera._initialized << endl;
	cout << "  Observer point:\t" << _camera._observer << endl;
	cout << "  Aimed point:\t\t" << _camera._aimedPoint << endl;
	cout << "  Way Up:\t\t" << _camera._wayUp << endl;
	cout << "  View Angle:\t\t" << _camera._viewAngle << endl;
	cout << "  Distance to Screen:\t" << _camera._distScreen << endl;
	cout << "  W3D:\t\t\t" << _camera._w3D << endl;
	cout << "  H3D:\t\t\t" << _camera._h3D << endl;
	cout << "  W2D:\t\t\t" << _camera._w2D << endl;
	cout << "  H2D:\t\t\t" << _camera._h2D << endl;
	cout << "  Ratio WH:\t\t" << _camera._ratioWH << endl;
	cout << "  Top-Left:\t\t" << _camera._screen3D[0] << endl;
	cout << "  Top-Right:\t\t" << _camera._screen3D[1] << endl;
	cout << "  Bottom-Left:\t\t" << _camera._screen3D[2] << endl;
	cout << "  Bottom-Right:\t\t" << _camera._screen3D[3] << endl;
}
