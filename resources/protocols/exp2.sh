# Learning curve experiments

DATASET="./data.txt"
NUM_RUNS=300000
TRIALS=5
POPULATION=500

DIR=`date +"%Y-%d-%mT%H-%M-%S"`
BasePath="./results/diversity_${DIR}"

mkdir -p ${BasePath}

LOOP="HFC"

# BGA Cross
METHOD="Cross"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 10)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
n
y
5
${NUM_RUNS}
${POPULATION}
${METHOD}
${LOOP}
0.5
4
10
" | ./SymReg
done