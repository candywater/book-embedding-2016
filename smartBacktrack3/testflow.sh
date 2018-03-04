nodes=(
#"10" "11" "12" "13" "14" "15"
)
card=(
  "0.1" "0.3" "0.5" "0.6" "0.75" "0.8" "0.9" "1.0"
    )
numbers=(
    "001" "002" "003" "004" "005" "006" "007" "008" "009" "010"
    "011" "012" "013" "014" "015" "016" "017" "018" "019" "020"
    )

dir1='../heuristic/data/random/graph'
dir2='../heuristic/data/ex-instances-PACE2017-public/stardard/'
dir3='test_data_dir/_20170124_random_10_14/output_'
run='./a.out'


#for i in "${nodes[@]}"
#do
#for j in "${card[@]}"
#do 
#    $run <${dir1}${i}_1_${j}.data >${dir3}${i}_1_${j}.data 1000
#    echo "$run <${dir1}${i}_1_${j}.data >${dir3}${i}_1_${j}.data 1000"
#done
#done

for i in "${numbers[@]}"
do 
 python3 $dir4 <${dir5}${i}.txt >${dir5}${i}.gph
 echo "python3 $dir4 <${dir5}${i}.txt >${dir5}${i}.gph"
 $run <${dir5}${i}.gph >${dir6}${i}.res
 echo "$run <${dir5}${i}.gph >${dir6}${i}.res"
done
