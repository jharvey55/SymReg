# Learning curve experiments

DATASET="./data.txt"
NUM_RUNS=300000
TRIALS=100
POPULATION=500

for j in $(seq 1 2)
do
DIR=`date +"%Y-%d-%mT%H-%M-%S"`
BasePath="./results/convergence_${DIR}"

mkdir -p ${BasePath}

LOOP="HFC"

# HFC Cross
METHOD="Cross"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 100)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
n
n
${NUM_RUNS}
${POPULATION}
${METHOD}
${LOOP}
0.5
4
10
" | ./SymReg
done
done