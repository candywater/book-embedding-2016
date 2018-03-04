nodes=(
    "10" "11" "12" "13" "14" "15"
)
card=(
  "0.1" "0.3" "0.5" "0.6" "0.75" "0.8" "0.9" "1.0"
    )

dir1='../heuristic/data/random/graph'
dir2='../heuristic/data/ex-instances-PACE2017-public/stardard/'
dir3='output_dir/random_20161223_10-15/output_'
run='./a.out'


for i in "${nodes[@]}"
do
for j in "${card[@]}"
do 
    $run <${dir1}${i}_1_${j}.data >${dir3}${i}_1_${j}.data 1000
    echo "$run <${dir1}${i}_1_${j}.data >${dir3}${i}_1_${j}.data 1000"
done
done
