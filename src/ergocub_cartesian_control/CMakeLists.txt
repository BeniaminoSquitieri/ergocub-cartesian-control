# SPDX-FileCopyrightText: 2025 Humanoid Sensing and Perception, Istituto Italiano di Tecnologia
# SPDX-License-Identifier: BSD-3-Clause

set(EXE_TARGET_NAME gb-ergocub-cartesian-control)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# YARP
find_package(YARP REQUIRED COMPONENTS
                           dev
                           os
                           sig
                           idl_tools
                           eigen
)

# Eigen3
find_package(Eigen3 REQUIRED)

# iDynTree
find_package(iDynTree REQUIRED)

# ProxSuite
find_package(proxsuite REQUIRED)

# BipedalLocomotionFramework (for logging)
find_package(BipedalLocomotionFramework 0.18.0
  COMPONENTS  VectorsCollection
              ParametersHandlerYarpImplementation REQUIRED)

# Executable
add_executable(${EXE_TARGET_NAME}
                include/DifferentialInverseKinematics.h
                include/DifferentialInverseKinematicsQP.h
                include/ForwardKinematics.h
                include/ForwardKinematicsiDynTree.h
                include/Integrator.h
                include/module.h
                src/DifferentialInverseKinematicsQP.cpp
                src/ForwardKinematicsiDynTree.cpp
                src/Integrator.cpp
                src/main.cpp
                src/module.cpp
                src/module_service.cpp
)

target_include_directories(${EXE_TARGET_NAME} PRIVATE
                                              ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${EXE_TARGET_NAME} PRIVATE
                                         YARP::YARP_dev
                                         YARP::YARP_init
                                         YARP::YARP_os
                                         YARP::YARP_sig
                                         YARP::YARP_eigen
                                         Eigen3::Eigen
                                         ${iDynTree_LIBRARIES}
                                         proxsuite::proxsuite
                                         gb-ergocub-cartesian-service
                                         cub-joint-control
                                         utils
                                         BipedalLocomotion::VectorsCollection
                                         BipedalLocomotion::ParametersHandlerYarpImplementation
                                         trajectory-generator
)

# Install the executable
install(TARGETS ${EXE_TARGET_NAME} DESTINATION bin)

# Install configuration and application files
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_right.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_right_sim.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_left.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_left_sim.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_left_r1.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_left_sim_r1.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_right_r1.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/config_right_sim_r1.ini DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/${EXE_TARGET_NAME})
