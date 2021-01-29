project(Wofenstein3D)

add_library(inventory SHARED
    Inventory.cpp
    PlayerWeapon.cpp 
    PWGun.cpp
    PWKnife.cpp
    PWMachineGun.cpp
    PWChainCannon.cpp
    PWRocketLauncher.cpp
)
