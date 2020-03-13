#!/bin/bash

cd "$(dirname "$(readlink -f "${0}")")"
 
# build by ndk
  
rm -rf obj/local/x86_64
rm -rf libs/x86_64
ndk-build APP_DEBUG:=false APP_ABI:=x86_64 NDK_PROJECT_PATH:=null NDK_OUT:=obj NDK_LIBS_OUT:=libs NDK_APPLICATION_MK:=Application.mk APP_BUILD_SCRIPT:=LinuxX11.mk 

# before execute change the rpath to \$ORIGIN  
  
chrpath -r '$ORIGIN' libs/x86_64/libPTMcRT.so

  
# copy the dep libs to out dir  
  
cp -f ../../../ThirdParty/PosixLinuxX11/Bionic-Redistributable/lib64/libc.so libs/x86_64
cp -f ../../../ThirdParty/PosixLinuxX11/Bionic-Redistributable/lib64/libdl.so libs/x86_64
cp -f ../../../ThirdParty/PosixLinuxX11/Bionic-Redistributable/lib64/libm.so libs/x86_64
cp -f ../../../ThirdParty/PosixLinuxX11/Bionic-Redistributable/lib64/libstdc++.so libs/x86_64  

