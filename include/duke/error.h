#pragma once
#include <string>
#include <vector>

namespace duke {

enum class ErrorCode {
    Ok = 0,
    InvalidNumber,
    UnknownArgument,
    InvalidId,
    MissingField,
    EmptyField,
    NegativeValue,
    InvalidType
};

inline std::string errorCause(ErrorCode c) {
    switch (c) {
        case ErrorCode::InvalidNumber: return "valor invalido";
        case ErrorCode::UnknownArgument: return "argumento desconhecido";
        case ErrorCode::InvalidId: return "ID invalido";
        case ErrorCode::MissingField: return "campo obrigatorio";
        case ErrorCode::EmptyField: return "campo vazio";
        case ErrorCode::NegativeValue: return "valor negativo";
        case ErrorCode::InvalidType: return "tipo invalido";
        default: return "";
    }
}

inline std::string errorMessage(ErrorCode c, const std::string& field = {}) {
    std::string cause = errorCause(c);
    if (field.empty() || cause.empty()) return cause;
    return field + ": " + cause;
}

struct ErrorDetail {
    ErrorCode code = ErrorCode::Ok;
    std::string field;
};

} // namespace duke

