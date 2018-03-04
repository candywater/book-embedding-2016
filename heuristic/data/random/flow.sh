
nodes=("5" "10" "20" "100" "200" "400" "500" "1200" "1600" "1800")
cardinality=("0.1" "0.3" "0.5" "0.6" "0.75" "0.8" "0.9" "1.0")
run='../../_input_format_converse_/contest_input_to_standard.py'
dir1='./heuristic/data/contest/'
dir2='./heuristic/data/'

for ix in "${nodes[@]}"
do
  for iy in "${cardinality[@]}"
  do
  python3 ${run} <./contest/graph${ix}_0_${iy}.data >graph${ix}_1_${iy}.data 
  echo "python3 ${run} <./contest/graph${ix}_0_${iy}.data >graph${ix}_1_${iy}.data "
  done
done

