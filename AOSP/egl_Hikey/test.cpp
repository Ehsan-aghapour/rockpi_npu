
    static int i=1;
    ALOGI("Ehsan:%d\n",i);
    i++;
    if(i%1000==0){
    char *mParamPath="/data/dataset/model.rknn";
    FILE *fp = fopen(mParamPath, "rb");
    if(fp == NULL) {
	//LOGE("fopen %s fail!\n", mParamPath);
	ALOGI("fopen %s fail!\n", mParamPath);
	return -1;
    }
    fseek(fp, 0, SEEK_END);
    int model_len = ftell(fp);
    void *model = malloc(model_len);
    fseek(fp, 0, SEEK_SET);
    if(model_len != fread(model, 1, model_len, fp)) {
	//LOGE("fread %s fail!\n", mParamPath);
	ALOGI("fread %s fail!\n", mParamPath);
	free(model);
	fclose(fp);
	return -1;
    }

    fclose(fp);

    // RKNN_FLAG_ASYNC_MASK: enable async mode to use NPU efficiently.
    //int ret = rknn_init(&ctx, model, model_len, RKNN_FLAG_PRIOR_MEDIUM|RKNN_FLAG_ASYNC_MASK);
    rknn_context ctx = 0;
    int ret = rknn_init(&ctx, model, model_len, RKNN_FLAG_PRIOR_MEDIUM);
    free(model);

	if(ret < 0) {
		//LOGE("rknn_init fail! ret=%d\n", ret);
		ALOGI("rknn_init fail! ret=%d\n", ret);
		return -1;
	}

	rknn_input_output_num io_num;
	ret = rknn_query(ctx, RKNN_QUERY_IN_OUT_NUM, &io_num, sizeof(io_num));
	if(ret < 0) {
		ALOGI("rknn_query fail! ret=%d\n",ret);
		return -1;
	}


	rknn_tensor_attr output0_attr;
	output0_attr.index = 0;
	ret = rknn_query(ctx, RKNN_QUERY_OUTPUT_ATTR, &output0_attr,
	sizeof(output0_attr));
	if(ret < 0) {
		ALOGI("rknn_query fail! ret=%d\n",ret);
		return -1;
	}


	rknn_tensor_attr input0_attr;
	input0_attr.index = 0;
	ret = rknn_query(ctx, RKNN_QUERY_INPUT_ATTR, &input0_attr,
	sizeof(input0_attr));
	if(ret < 0) {
		ALOGI("rknn_query fail! ret=%d\n",ret);
		return -1;
	}




	ALOGI("\n\n*************\n");
	print_attr(input0_attr);
	ALOGI("\n\n*************\n");
	print_attr(output0_attr);

	float data[475];
	for(int i=0;i<475;i++){
		data[i]=i;
	}
	rknn_input inputs[1];
	inputs[0].index = 0;
	inputs[0].buf = data;
	inputs[0].size = sizeof(data);
	inputs[0].pass_through = false;
	//inputs[0].pass_through = true;
	//inputs[0].type = RKNN_TENSOR_UINT8;
	inputs[0].type = RKNN_TENSOR_FLOAT32;
	inputs[0].fmt = RKNN_TENSOR_NHWC;
	ret = rknn_inputs_set(ctx, 1, inputs);
	if(ret < 0) {
		ALOGI("rknn_input_set fail! ret=%d\n", ret);
		return -1;
	}



	rknn_output outputs[1];
	outputs[0].want_float = true;
	outputs[0].is_prealloc = false;




	//t1=std::chrono::high_resolution_clock::now();
	ret = rknn_run(ctx, NULL);
	if(ret < 0) {
		ALOGI("rknn_run fail! ret=%d\n", ret);
		return -1;
	}
	//t2=std::chrono::high_resolution_clock::now();




	ret = rknn_outputs_get(ctx, 1, outputs, NULL);
	if(ret < 0) {
		ALOGI("rknn_outputs_get fail! ret=%d\n", ret);
		return -1;
	}
	//auto t3=std::chrono::high_resolution_clock::now();

	//double run_latency=std::chrono::duration_cast<std::chrono::duration<double>>(t2-t1).count();
	//double getout_latency=std::chrono::duration_cast<std::chrono::duration<double>>(t3-t2).count();
	//ALOGI("\nrun latency:%f \t get output latency:%f \n",1000.0*run_latency,1000.0*getout_latency);


	_rknn_perf_run run_time;
	ret = rknn_query(ctx, RKNN_QUERY_PERF_RUN, &run_time,sizeof(run_time));
	if(ret < 0) {
		ALOGI("rknn_query fail! ret=%d\n",ret);
		return -1;
	}
	ALOGI("run_time:%ld\n",run_time.run_duration);


	_rknn_sdk_version version;
	ret = rknn_query(ctx, RKNN_QUERY_SDK_VERSION, &version,sizeof(version));
	if(ret < 0) {
		ALOGI("rknn_query fail! ret=%d\n",ret);
		return -1;
	}
	ALOGI("api version:%s \t drive version:%s \n",version.api_version,version.drv_version);


	//print_output(outputs[0]);
	ALOGI("\n\n*************\n");
	print_input(inputs[0],input0_attr.n_elems);
	ALOGI("\n\n*************\n");
	print_output(outputs[0],output0_attr.n_elems);

	rknn_outputs_release(ctx, 1, outputs);

	rknn_destroy(ctx);

	}
