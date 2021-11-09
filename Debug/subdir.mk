################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Agent.cpp \
../Ant.cpp \
../AntBase.cpp \
../AntBasePheromone.cpp \
../Anthill.cpp \
../Environment.cpp \
../Food.cpp \
../Pheromone.cpp \
../Renderer.cpp \
../SillyAnt.cpp \
../Timer.cpp \
../main.cpp 

OBJS += \
./Agent.o \
./Ant.o \
./AntBase.o \
./AntBasePheromone.o \
./Anthill.o \
./Environment.o \
./Food.o \
./Pheromone.o \
./Renderer.o \
./SillyAnt.o \
./Timer.o \
./main.o 

CPP_DEPS += \
./Agent.d \
./Ant.d \
./AntBase.d \
./AntBasePheromone.d \
./Anthill.d \
./Environment.d \
./Food.d \
./Pheromone.d \
./Renderer.d \
./SillyAnt.d \
./Timer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I"D:\C++_workspace\Ants_v3.tar.gz_expanded\Ants_v3" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


