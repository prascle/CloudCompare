option( PLUGIN_STANDARD_QHPR "Install qHPR plugin" OFF )

if( PLUGIN_STANDARD_QHPR )
	project( QHPR_PLUGIN )
		
	AddPlugin( NAME ${PROJECT_NAME} )

    option( USE_EXTERNAL_QHULL_FOR_QHPR "Use external QHull for qHPR plugin" OFF )
    configure_file(include/optdefineshpr.h.in include/optdefineshpr.h)

    if ( USE_EXTERNAL_QHULL_FOR_QHPR )
        include( cmake/FindQhull.cmake )
        
        target_include_directories( ${PROJECT_NAME} PUBLIC
            ${QHULL_INCLUDE_DIR}
        )
    else()
        add_subdirectory( extern/qhull EXCLUDE_FROM_ALL )
    endif()

	add_subdirectory( include )
	add_subdirectory( src )
	add_subdirectory( ui )
		
	target_link_libraries( ${PROJECT_NAME} qhull )
endif()
