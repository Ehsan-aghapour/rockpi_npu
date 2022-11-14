from onnx import version_converter, helper
import onnx
model=onnx.load_model(‘model.onnx’)
converted_model=version_converter.convert_version(model, 9)
onnx.save(converted_model,’cmodel.onnx’)
