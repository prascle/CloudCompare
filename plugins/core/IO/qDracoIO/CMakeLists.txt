option( PLUGIN_IO_QDRACO "Install qDracoIO plugin to read & write DRC files" OFF )

if( PLUGIN_IO_QDRACO )
	project( QDRACO_IO_PLUGIN )

	find_package( Draco REQUIRED )

	AddPlugin( NAME ${PROJECT_NAME} TYPE io )

	if( MSVC )
		message (STATUS "MSVC detected, linking with Draco libraries...")
		target_include_directories( ${PROJECT_NAME} PRIVATE ${DRACO_INCLUDE_DIRS} )

		if ( USE_CONDA_PACKAGES )
			target_link_libraries( ${PROJECT_NAME} ${DRACO_LIBRARIES} )
		else()
			target_link_libraries( ${PROJECT_NAME} ${DRACO_LIBRARIES} )
			#target_link_libraries( ${PROJECT_NAME} ${Draco_DIR}/../../lib/${DRACO_LIBRARIES}.lib )
		endif()

	else()

		target_link_libraries( ${PROJECT_NAME} ${DRACO_LIBRARIES} )

	endif()
    message("link ${PROJECT_NAME} with ${DRACO_LIBRARIES}")

	message (STATUS "DRACO_INCLUDE_DIRS ${DRACO_INCLUDE_DIRS}")

	add_subdirectory( include )
	add_subdirectory( src )
	add_subdirectory( ui )
 
endif()
