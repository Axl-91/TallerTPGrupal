project(Wofenstein3D)

add_library(inventory SHARED
    Inventory.cpp
    PlayerWeapon.cpp 
    PWGun.cpp
    PWKnife.cpp
    PWMachineGun.cpp
    PWChainCanon.cpp
    PWRocketLauncher.cpp
)
