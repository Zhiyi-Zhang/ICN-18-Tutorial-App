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

Also, generate a new identity in your NDN keychain by:
```
ndnsec-key-gen /ndn/edu/ucla/alice
```

### 3. Run applications

```
./producer
```
The producer will reply Data packets signed by the key imported from `camera.prv.key` and packets signed by the self-generated key `/ndn/edu/ucla/alice` in turn.

```
./consumer
```
The consumer is able to validate the Data packets signed by the key imported from `camera.prv.key` but cannot validate packets signed by `/ndn/edu/ucla/alice`.

### 4. Remove the example identity and corresponding key pairs from your local NDN key chain

```
ndnsec-delete /home/LivingRoom/Camera-01
ndnsec-delete /ndn/edu/ucla/alice
```

