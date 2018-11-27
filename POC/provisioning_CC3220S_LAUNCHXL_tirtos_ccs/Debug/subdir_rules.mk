################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me --include_path="/Users/kristinabrunsgaard/workspace_v8/provisioning_CC3220S_LAUNCHXL_tirtos_ccs" --include_path="/Applications/ti/simplelink_cc32xx_sdk_2_30_00_05/source/ti/posix/ccs" --include_path="/Applications/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


