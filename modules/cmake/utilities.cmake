#macro to retrieve GAMBIT modules
macro(retrieve_bits bits root excludes quiet)

  set(${bits} "")
  file(GLOB children RELATIVE ${root} ${root}/*Bit*)

  foreach(child ${children})
    if(IS_DIRECTORY ${root}/${child})

      # Work out if this Bit should be excluded or not.
      set(excluded "NO")
      foreach(x ${excludes})
        string(FIND ${child} ${x} location)
        if(${location} EQUAL 0) 
          set(excluded "YES")
        endif()
      endforeach()      

      # Exclude or add this bit.
      if(${excluded})
        if(NOT ${quiet} STREQUAL "Quiet") 
          message("   Excluding ${child} from GAMBIT configuration.")
        endif()
      else()
        list(APPEND ${bits} ${child})
      endif()

    endif()
  endforeach()

endmacro()

include(CMakeParseArguments)
# function to add static GAMBIT library
function(add_gambit_library libraryname)
  cmake_parse_arguments(ARG "" "OPTION" "SOURCES;HEADERS" "" ${ARGN})

  add_library(${libraryname} ${ARG_OPTION} ${ARG_SOURCES} ${ARG_HEADERS})
  add_dependencies(${libraryname} model_harvest)
  add_dependencies(${libraryname} backend_harvest)
  add_dependencies(${libraryname} functor_harvest)

  if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    foreach (dir ${GAMBIT_INCDIRS})
      target_include_directories(${libraryname} PUBLIC ${dir})
    endforeach()
  else()
    foreach (dir ${GAMBIT_INCDIRS})
      include_directories(${dir})
    endforeach()
  endif()

  if(${ARG_OPTION} STREQUAL SHARED AND APPLE)
    set_property(TARGET ${libraryname} PROPERTY SUFFIX .so)
  endif()

endfunction()


# function to add GAMBIT executable
function(add_gambit_executable executablename)
  cmake_parse_arguments(ARG "" "" "SOURCES;HEADERS;" "" ${ARGN})

  add_executable(${executablename} ${ARG_SOURCES} ${ARG_HEADERS})

  if(${CMAKE_VERSION} VERSION_GREATER 2.8.10)
    foreach (dir ${GAMBIT_INCDIRS})
      target_include_directories(${executablename} PUBLIC ${dir})
    endforeach()
  else()
    foreach (dir ${GAMBIT_INCDIRS})
      include_directories(${dir})
    endforeach()
  endif()

  if (MPI_FOUND)
    set(LIBRARIES ${LIBRARIES} ${MPI_CXX_LIBRARIES})
  endif()
  if (yaml_FOUND)
    set(LIBRARIES ${LIBRARIES} ${yaml_LDFLAGS})
  endif()
  if (GSL_FOUND)
    if(GSL_LDFLAGS)
      set(LIBRARIES ${LIBRARIES} ${GSL_LDFLAGS})
    else()
      set(LIBRARIES ${LIBRARIES} "-L${GSL_LIBRARY_DIRS}")
      foreach(LIB ${GSL_LIBRARIES})
        set(LIBRARIES ${LIBRARIES} ${LIB})
      endforeach()
    endif()
  endif()
  if (LIBDL_FOUND)
    set(LIBRARIES ${LIBRARIES} ${LIBDL_LIBRARY})
  endif()

#  message(STATUS ${LIBRARIES})

  target_link_libraries(${executablename} ${LIBRARIES})
endfunction()