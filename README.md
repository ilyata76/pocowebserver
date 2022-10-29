# pocowebserver
POCO C++ web server
```
docker-compose --env-file .\.env up --build
```
Для сборки средствами `cmake` из папки `build`:
```
cmake -E env POSTGRES_ROOT=path/to/postgres cmake ..
```
