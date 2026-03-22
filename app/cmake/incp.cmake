include(FetchContent)

FetchContent_Declare(
    pyincp
    GIT_REPOSITORY ssh://git@repo.dsi.tecnico.ulisboa.pt/nanosatlab/istsat-2/incp.git
    GIT_TAG develop
)

FetchContent_MakeAvailable(pyincp)
