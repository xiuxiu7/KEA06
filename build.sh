#!/bin/sh

# if no argument use interactive promt, otherwise use arugment
if [ $# -eq 1 ]; then
  build_type=$1

  echo "Build type is ${build_type}"

else
  # set default
  build_type=Debug

  # choose build type
  while true; do
    read -p "$(echo "Choose build type:\n 1-Debug(default)\n 2-Release\n=>")" answer
      case ${answer} in
          1 ) build_type=Debug; echo "Build type is ${build_type}"; break;;
          2 ) build_type=Release; echo "Build type is ${build_type}"; break;;
          * ) echo "Use default. Build type is ${build_type}"; break;;
      esac
  done

fi

project_dir=${PWD}

rm -rf build/${build_type}
mkdir -p build/${build_type}
cd build/${build_type}

cmake ${project_dir} -DTHREADS_PTHREAD_ARG=2 -DCMAKE_TOOLCHAIN_FILE=${project_dir}/toolchain.cmake -DCMAKE_BUILD_TYPE=${build_type}
