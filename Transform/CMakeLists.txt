add_llvm_loadable_module(MyPass
    DCE.cpp
    CSE.cpp

    PLUGIN_TOOL
    opt)
