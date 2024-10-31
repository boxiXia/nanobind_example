# minimum example to bind cmake c++ code using nanobind in an conda/mamba environment with vscode

this example runs the nanobind example in referenced official doc: https://nanobind.readthedocs.io/en/latest/building.html

## setup an conda/mamba python virtual environment

If you want to setup nanobind in an virtual environment, the only necessary step is to install nanobind with pip:

```bash
conda activate [YOUR_VIRTUAL_ENVIRONMENT]
pip install nanobind
```

Or you can start with an new virtual environment named `py38` for example:
```
conda env create --file conda_env.yaml
```

### setup environment variable
first find out the location of `Python_EXECUTABLE`
```bash
## replace py38 with virtual environment name
conda acitvate py38
## find Python_EXECUTABLE
whereis python
```

<!-- first find out the location of `Python_EXECUTABLE`
, `PYTHON_LIBRARY` and `PYTHON_INCLUDE_DIR` inside your virtual environment (`py38` for example):

```bash
## replace py38 with virtual environment name
conda acitvate py38
## find Python_EXECUTABLE
whereis python

## find PYTHON_LIBRARY
echo $CONDA_PREFIX/lib/libpython3.so
## use ...libpython3.so

## find PYTHON_INCLUDE_DIR
echo $CONDA_PREFIX/include
``` -->

You will then replace these three variables in [`./.vscode/settings.json`](./.vscode/settings.json)

### build the example
You can use either option

#### option 1: use vscode cmake plugin to build
search in the vscode extension marketplace and install `go2sh.cmake-integration-vscode`.
then press `F1` and search `cmake:build`, run it to compile

#### option 2: compile with commandline
```bash
# use the actual Python_EXECUTABLE you find in previous step
cmake -DPython_EXECUTABLE=$HOME/repo/micromamba/envs/py38/bin/python -S$(pwd) -B$(pwd)/build -G Ninja
```

## run python

```bash
## replace py38 with virtual environment name
conda acitvate py38
python test_my_ext.py
```