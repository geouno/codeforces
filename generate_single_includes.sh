# /bin/bash

python3 amalgamation.py -I include -S include/geouno/codeforces.hpp -T single_include/geouno/codeforces.hpp
python3 amalgamation.py -I include -S include/geouno/codeforces.hpp -T single_include_json_dependent/geouno/codeforces.hpp \
--no-expand "geouno/third_party/json.hpp"
