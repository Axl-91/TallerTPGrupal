project(Wofenstein3D)

add_library(sp_inventory SHARED
    SInventory.cpp
    SPWeapon.cpp 
    SPWGun.cpp
    SPWKnife.cpp
    SPWMachineGun.cpp
    SPWChainCannon.cpp
)
