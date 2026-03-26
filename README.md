# DKV Client
DKV Client - a lightweight C++ client for interacting with [DKV distributed key-value store](https://github.com/metrofun-repo/DKV-Storage). Provides a simple API for performing GET/SET/DELETE operations over HTTP

## Purpose
The client offers a minimal C++ API for communication with DKV nodes and provides CLI tool for testing

## Dependencies
|    Library   |	                 Purpose                      |
|--------------|------------------------------------------------|
| [cpp-httplib](https://github.com/yhirose/cpp-httplib)  |	HTTP client for REST communication|
|[nlohmann::json](https://github.com/nlohmann/json)|	JSON serialization/deserialization            |
|[GoogleTest (gtest)](https://github.com/google/googletest)|	unit testing framework |

## Features
- JSON request/response handling
- Unified error handling model
- Simple CLI for manual testing 

## Usage (CLI)
Supported  commands:
|command|args|description|
|-------|----|-----------|
| set| key, value| send set key value request to distributed store|
| get|key|get value for given key from distributed store
|remove|key|remove key and corresponding value from distributed store|
|help|-|show help message|
|exit|-|exit the client|

Examples:
```bash
dkv-client [127.0.0.1:8080] > set test value
dkv-client [127.0.0.1:8080] > get test
dkv-client [127.0.0.1:8080] > remove test
```

## API Overview
|Command|HttpMethod|Endpoint|Description|
|------|--------|-----------|-----------|
|get|GET|/kv?key={key}|get value request|
|set|POST|/kv?key={key} body{"value": value}| set value request|
|remove|DELETE|/kv?key={key}| remove key|

## Quick Start

### Start DKV Client
Client requires:
 - '--host' - IP address of DKV node
 - '--port' - port of DKV node

```bash
./dkv_client --host 127.0.0.1 --port 8080
```
## Project Structure

```
src/
   api/    - high-level client API
   app/    - app entry point
   cli/    - CLI tool
   config/ - app config
   core/   - error handling types
   http/   - HTTP wrapper
tests/     - unit tests
third-party/ - third-party lib
```