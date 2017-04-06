### CMakeLists.txt --- PolytechRayTracing project
## 
## Author: Jean-Christophe Lombardo
## Copyright (C) 2011 - Jean-Christophe Lombardo, Inria
## Created: Thu Jun  9 10:33:56 2011
## Last-Updated:  Thu Jun  9 17:25:07 2011
##           By: Jean-Christophe Lombardo
##
######################################################################

#################################
#
# To add several exec
#
# set(CMAKE_CXX_FLAGS "-Wall -g")
#
# add_executable(nom_executable
# 					fichier1
# 					fichier2)
#
#################################

set(CMAKE_CXX_FLAGS "-Wall -g")


project(appGui)

set(${PROJECT_NAME}_HEADERS
    Color.h
    Cylindre.h
    Draughtboard.h
    Image.h
    ImageTexture.h
    LightModel.h
    LightSource.h
    MarbleTexture.h
    Material.h
    Matrix3.h
    NoiseTexture.h
    #ParamSurf.h
    PhongModel.h
    Plane.h
    Quadrics.h
    Ray.h
    RayTracer.h
    Rectangle.h
    RNG.h
    Scene.h
    SceneParser.h
    ScreenV2.h
    Set.h
    Shape.h
    SimpleTexture.h
    SolidNoise.h
    Sphere.h
    #stdint.h
    Texture.h
    Timer.h
    tinystr.h
    tinyxml.h
    UVSphere.h
    Vector2.h
    Vector3.h
)

set(${PROJECT_NAME}_SOURCES
    Color.cpp
    Cylindre.cpp
    Draughtboard.cpp
    Image.cpp
    ImageTexture.cpp
    LightModel.cpp
    LightSource.cpp
    MarbleTexture.cpp
    Material.cpp
    Matrix3.cpp
    NoiseTexture.cpp
    #ParamSurf.cpp
    PhongModel.cpp
    Plane.cpp
    Quadrics.cpp
    Ray.cpp
    RayTracer.cpp
    Rectangle.cpp
    RNG.cpp
    Scene.cpp
    SceneParser.cpp
    ScreenV2.cpp
    Shape.cpp
    SimpleTexture.cpp
    SolidNoise.cpp
    Sphere.cpp
    Texture.cpp
    Timer.cpp
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
    UVSphere.cpp
    Vector2.cpp
    Vector3.cpp
)

#add_definitions(-std=c++0x)

add_executable(${PROJECT_NAME}
        main.cpp
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_HEADERS}
    )
	
target_link_libraries(${PROJECT_NAME}
        ${SDL_LIBRARY}
        ${SDLIMAGE_LIBRARY}
        ${ITPP_LIBRARY}
)

## -*- tab-width: 4; indent-tabs-mode: nil c-basic-offset: 4 -*-
## vim:cindent:ts=4:sw=4:et:tw=80:sta:

