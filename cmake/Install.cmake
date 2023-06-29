include(GNUInstallDirs)

set(BOOST_TARGETS boost_statechart boost_assert boost_bind boost_config
    boost_conversion boost_core boost_detail boost_function boost_mpl
    boost_smart_ptr boost_static_assert boost_thread boost_type_traits
    boost_throw_exception boost_typeof boost_integer boost_type_index
    boost_atomic boost_chrono boost_concept_check boost_container
    boost_container_hash boost_date_time boost_exception boost_intrusive
    boost_io boost_iterator boost_move boost_optional boost_predef
    boost_preprocessor boost_system boost_tuple boost_utility boost_winapi
    boost_algorithm boost_lexical_cast boost_align boost_ratio
    boost_describe boost_mp11 boost_numeric_conversion boost_functional
    boost_tokenizer boost_function_types boost_fusion boost_variant2
    boost_regex boost_unordered boost_array boost_range boost_rational
)
install(TARGETS ${BOOST_TARGETS} precompiled infrastructure_obj infrastructure_shared infrastructure_static
    EXPORT InfrastructureLibrary
    ARCHIVE COMPONENT infrastructure_dev
    LIBRARY COMPONENT infrastructure
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/infrastructure
        COMPONENT infrastructure
)
 
if(UNIX)
    install(CODE "execute_process(COMMAND ldconfig)"
        COMPONENT infrastructure
    )
endif()

install(EXPORT InfrastructureLibrary
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${MY_PROJECT_NAME}/cmake
    NAMESPACE ${MY_PACKAGE_NAME}::Infrastructure::
    COMPONENT infrastructure
)

install(FILES "ProjectConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/${CMAKE_PROJECT_NAME}/cmake
    RENAME "${MY_PACKAGE_NAME}Config.cmake"
)

set(CPACK_PACKAGE_VENDOR "Mohammad Rahimi")
set(CPACK_PACKAGE_CONTACT "rahimi.mhmmd@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION "Qt StateMachine vs. Boost Statechart")
include(CPack)
