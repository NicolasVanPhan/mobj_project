# -*- explicit-buffer-name: "CMakeLists.txt<M1-MOBJ/6>" -*-
#
# To display executed commands, use:
#     > cmake -DCMAKE_VERBOSE_MAKEFILE:STRING=YES ../src

 cmake_minimum_required(VERSION 2.8.0)
 project(SCHEMATIC)

# Detection of LibXml2
find_package(LibXml2)
 
 set (CMAKE_CXX_FLAGS            "-Wall -g" CACHE STRING "C++ Compiler Release options." FORCE)
 set (CMAKE_INSTALL_PREFIX       "../install" )


    include_directories( ${SCHEMATIC_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR} )

                    set( includes     Indentation.h
                                      Term.h
                                      Net.h
                                      Instance.h
                                      Point.h
                                      Node.h
                                      Cell.h
                                      XmlUtil.h
                                      Box.h
                                      Line.h
                                      Symbol.h
                                      Shape.h
                                      BoxShape.h
                                      TermShape.h
                                      LineShape.h
                                      EllipseShape.h
                                      ArcShape.h
                       )

                    set( cpps         Indentation.cpp
                                      Term.cpp
                                      Net.cpp
                                      Instance.cpp
                                      Point.cpp
                                      Node.cpp
                                      Cell.cpp
                                      Main.cpp
                                      XmlUtil.cpp
                                      Box.cpp
                                      Line.cpp
                                      Symbol.cpp
                                      Shape.cpp
                                      BoxShape.cpp
                                      TermShape.cpp
                                      LineShape.cpp
                                      EllipseShape.cpp
                                      ArcShape.cpp
                       )

# Make linking with LibXml2
        add_executable ( tme7        ${cpps} )
        target_link_libraries ( tme7 ${LIBXML2_LIBRARIES} )
               install ( TARGETS      tme7        DESTINATION bin )
               install ( FILES        ${includes}  DESTINATION include )
