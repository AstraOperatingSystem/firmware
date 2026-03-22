find_program(ASN1SCC NAMES asn1scc)

set(INCP_SCHEMA ${CMAKE_CURRENT_SOURCE_DIR}/schema.yml)
set(INCP_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(ASN1_OUTPUT ${INCP_OUTPUT_DIR}/gen.asn1)
set(ASN1SCC_SOURCES
    ${INCP_OUTPUT_DIR}/gen.c
    ${INCP_OUTPUT_DIR}/asn1crt.c
    ${INCP_OUTPUT_DIR}/asn1crt_encoding.c
    ${INCP_OUTPUT_DIR}/asn1crt_encoding_uper.c
)
set(ASN1SCC_HEADERS
    ${INCP_OUTPUT_DIR}/gen.h
    ${INCP_OUTPUT_DIR}/asn1crt.h
    ${INCP_OUTPUT_DIR}/asn1crt_encoding.h
    ${INCP_OUTPUT_DIR}/asn1crt_encoding_uper.h
)
set(WRAPPER_SOURCE ${INCP_OUTPUT_DIR}/gen_wrapper.c)
set(WRAPPER_HEADER ${INCP_OUTPUT_DIR}/gen_wrapper.h)
set(INCP_SOURCES
    ${ASN1SCC_SOURCES}
    ${WRAPPER_SOURCE}
)

# Generates the ASN1 code
add_custom_command(
    OUTPUT ${ASN1_OUTPUT}
    COMMAND
        ${CMAKE_COMMAND} -E env
        pyincp codegen --asn1 ${INCP_OUTPUT_DIR} ${INCP_SCHEMA}
    MAIN_DEPENDENCY ${INCP_SCHEMA}
    COMMENT "INCP: Generating ASN1 definition"
    VERBATIM
)

# Compiles the ASN1 code to C
add_custom_command(
    OUTPUT
        ${ASN1SCC_SOURCES}
        ${ASN1SCC_HEADERS}
    COMMAND
        ${ASN1SCC} -c -uPER --slim --word-size 4 --handle-empty-sequences -if BitStream_AppendByteArray -if BitStream_DecodeConstraintWholeNumber -if BitStream_EncodeConstraintWholeNumber -o ${INCP_OUTPUT_DIR} ${ASN1_OUTPUT}
    MAIN_DEPENDENCY ${ASN1_OUTPUT}
    COMMENT "INCP: Compiling ASN1 definition"
    VERBATIM
)

# Generates the C wrapper
add_custom_command(
    OUTPUT
        ${WRAPPER_SOURCE}
        ${WRAPPER_HEADER}
    COMMAND
        ${CMAKE_COMMAND} -E env
        pyincp codegen --c ${INCP_OUTPUT_DIR} ${INCP_SCHEMA}
    MAIN_DEPENDENCY ${INCP_SCHEMA}
    COMMENT "INCP: Generating C wrapper"
    VERBATIM
)

add_custom_target(generate_incp
	DEPENDS
		${WRAPPER_SOURCE}
		${WRAPPER_HEADER}
		${ASN1SCC_SOURCES}
        ${ASN1SCC_HEADERS}
	)

add_dependencies(astra-os-fw generate_incp)

# Integrate generated artifacts with the project's build
target_sources(astra-os-fw PRIVATE
    ${INCP_SOURCES}
)

target_include_directories(astra-os-fw PRIVATE
    ${INCP_OUTPUT_DIR}
)
