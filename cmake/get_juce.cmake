# Note: we only need to supply the GIT_TAG because the JUCE version in Github doesn't have the preceding v (i.e v7.0.12).
# If it had the preceding v we could just supply the VERSION (and the other arguments).
CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.12
    VERSION 7.0.12
    SOURCE_DIR ${DEPENDENCIES_DIR}/juce
)
