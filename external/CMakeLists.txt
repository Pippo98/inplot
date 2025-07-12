message("[External]")
set(CDIR ${CMAKE_CURRENT_LIST_DIR})

set(EXTERNAL_DIRS
  ${CDIR}
)
include_directories(PUBLIC ${EXTERNAL_DIRS})




set(EXTERNAL_DIRS ${EXTERNAL_DIRS} PARENT_SCOPE)
