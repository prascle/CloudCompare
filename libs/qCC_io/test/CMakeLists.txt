find_package(Qt6 REQUIRED COMPONENTS Test)

if ( OPTION_USE_SHAPE_LIB )
    add_executable( TestShpFilter )

    target_sources( TestShpFilter
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/TestShpFilter.cpp
            ${CMAKE_CURRENT_LIST_DIR}/TestShpFilter.h
            ${CMAKE_CURRENT_LIST_DIR}/TestData.qrc
    )

	if( NOT APPLE )
        target_link_libraries( TestShpFilter
            PRIVATE
                QCC_IO_LIB
                Qt6::Test
    		    "-static-libstdc++"
		)
    else()
        target_link_libraries( TestShpFilter
            PRIVATE
                QCC_IO_LIB
                Qt6::Test
        )
	endif()

    if ( WIN32 )
        set_target_properties( TestShpFilter PROPERTIES
            WIN32_EXECUTABLE False
        )
    endif()

    add_test( NAME TestShpFilter COMMAND TestShpFilter )
endif()



