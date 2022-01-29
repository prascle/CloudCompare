option( PLUGIN_IO_QDRACO "Install qDracoIO plugin to read & write DRC files" OFF )

if( PLUGIN_IO_QDRACO )
	project( QDRACO_IO_PLUGIN )

	find_package( Draco REQUIRED )

	AddPlugin( NAME ${PROJECT_NAME} TYPE io )
	
	target_include_directories( ${PROJECT_NAME} PRIVATE ${DRACO_INCLUDE_DIR} )
	if (MSVC)
		target_link_libraries( ${PROJECT_NAME} optimized ${DRACO_LIBRARY} )
	else()
		target_link_libraries( ${PROJECT_NAME} optimized ${DRACO_LIBRARY} )
		message("link ${PROJECT_NAME} with ${DRACO_LIBRARY}")
	endif()

	message (STATUS "DRACO_INCLUDE_DIR ${DRACO_INCLUDE_DIR}")
	message (STATUS "DRACO_LIBRARY ${DRACO_LIBRARY}")

	add_subdirectory( include )
	add_subdirectory( src )
	add_subdirectory( ui )
 
endif()
