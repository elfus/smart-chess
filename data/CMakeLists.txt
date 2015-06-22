file(GLOB SMARTCHESS_DATA_FILES "*")

foreach(data_file ${SMARTCHESS_DATA_FILES})
	message(STATUS "Copying data file: ${data_file}")
	file(COPY ${data_file} DESTINATION ${SMARTCHESS_DATA_DIR})
endforeach(data_file)
