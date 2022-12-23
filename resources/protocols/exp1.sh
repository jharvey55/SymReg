# Learning curve experiments

DATASET="./data.txt"
NUM_RUNS=500000
TRIALS=5
POPULATION=500
SURVIVAL_RATE=0.5

DIR=`date +"%Y-%d-%mT%H-%M-%S"`
BasePath="./results/learning_${DIR}"

mkdir -p ${BasePath}

LOOP="BGA"

# BGA Random
METHOD="Random"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 10)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
y
n
${NUM_RUNS}
${POPULATION}
${METHOD}
${LOOP}
" | ./SymReg
done

# BGA RMHC
METHOD="RMHC"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 10)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
y
n
${NUM_RUNS}
${POPULATION}
${METHOD}
${LOOP}
" | ./SymReg
done

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
y
n
${NUM_RUNS}
${POPULATION}
${METHOD}
${LOOP}
" | ./SymReg
done

LOOP="HFC"

# TODO: HFC RMHC
METHOD="RMHC"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 10)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
y
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

# HFC Cross
METHOD="Cross"
echo "Beginning ${LOOP}-${METHOD}"
RPATH="${BasePath}/${METHOD}/"
mkdir -p ${RPATH}

for i in $(seq 1 10)
do
echo "${LOOP}-${METHOD} Trial: ${i} of ${TRIALS}"
echo "${DATASET}
${RPATH}
y
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