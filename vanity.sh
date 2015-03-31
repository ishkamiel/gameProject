#!/bin/bash

wc $(find engine -name '*.cpp' -or -name '*.h') $(find demo -name '*.cpp' -or -name '*.h')
