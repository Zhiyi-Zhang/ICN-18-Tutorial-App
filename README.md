# Play With Schematized Trust in NDN

## Instructions

### 0. Have dependencies installed

Please install NDN-CXX and NFD into your local system and have NFD running.
For more details, please go visit install instructions for [ndn-cxx](https://github.com/named-data/ndn-cxx/blob/master/docs/INSTALL.rst) and [nfd](https://github.com/named-data/NFD/blob/master/docs/INSTALL.rst).

### 1. Compile the code

```
make
```

### 2. Import example identity with public private key pair into your local NDN key chain

```
ndnsec-import camera.prv.key
```

### 3. Run applications

```
./producer
```

```
./consumer
```

### 4. Remove the example identity and corresponding key pairs from your local NDN key chain

```
ndnsec-delete /home/LivingRoom/Camera-01
```

