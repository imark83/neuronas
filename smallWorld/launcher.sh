#!/bin/bash
for i in {1..12}
do
   ./aaa > neuronShort$i.bin &
done
