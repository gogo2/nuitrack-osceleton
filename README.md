# nuitrack-osceleton

Nuitrack-osceleton is a program that takes skeleton data from any depth sensor supported by [Nuitrack](https://nuitrack.com/)
and sends joints coordinates via OSC.

It is a modern rewrite [OSCeleton](https://github.com/Sensebloom/OSCeleton) for Nuitrack middleware.  
Original OSCeleton becomes more and more obsolete as OpenNI 1.x and NiTE are no longer available for public use.  
For now it supports only basic, main features of original OSCeleton.

## Requirements
* Building process of nuitrack-osceleton is managed by [CMake](https://cmake.org/)
* Nuitrack-osceleon depends Nuitrack and NuitrackSDK which can be downloaded from [here](https://download.3divi.com/Nuitrack/)
* For OSC we use liblo which is included in repository
* Modern C++ compiler (project is set to C++14, but probably C++11 will also be sufficient)

## Compilation
as any CMake project


## Usage
 ```
  OSCeleton [OPTION...]
  -a, --address arg  OSC server address (default: 127.0.0.1)
  -p, --port arg     OSC server port (default: 7110)
  -r, --reverse      Disable mirror mode
  -h, --help         Help
  ```

### Message format
* Joint data: `/joint user_id joint_name x y z`
* On new user event: `/new_user`
* On lost user event: `/lost_user`


## TODO
* implement more features of original OSCeleton
* better docs


