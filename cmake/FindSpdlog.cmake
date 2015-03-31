find_path(Spdlog_INCLUDE_DIR spdlog/spdlog.h
    HINTS
    $ENV{SPDLOG_HOME}
    PATH_SUFFIXES spdlog/include include
    PATHS
    /usr/local/include/spdlog
    /usr/include/spdlog
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Spdlog 
    REQUIRED_VARS 
    Spdlog_INCLUDE_DIR)
