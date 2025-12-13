#include "scanner.h"
#include <stdio.h>

Scanner scanner;

void debugScanner() {
  printf(">>>>>> Debugging Scanner <<<<<<\n");
  printf("Scanner Token Start Pos: %ld\n", scanner.TokenStartPos);
  printf("Scanner Token Cur Pos: %ld\n", scanner.TokenCurrPos);
}

void InitScanner(const char *pfilePath) {
  FILE *pfile = ReadFile(pfilePath);

  scanner.pTokenCurrent = pfile;
  scanner.TokenStartPos = 0;
  scanner.TokenCurrPos = 0;
  scanner.Line = 1;
}

void saveScannerPos(bool isTokenStartPos) {
  if (isTokenStartPos) {
    scanner.TokenStartPos = ftell(scanner.pTokenCurrent);
  } else {
    scanner.TokenCurrPos = ftell(scanner.pTokenCurrent);
  }
}

void updateScanner() {
  saveScannerPos(false);
  scanner.TokenStartPos = scanner.TokenCurrPos;
}
void increaseScannerLine() { scanner.Line++; }

Token makeToken(TokenType tokenType) {
  saveScannerPos(false);

  Token token;
  token.TokenType = tokenType;
  token.OffsetFromStart = (scanner.TokenStartPos - 0);
  token.Length = (scanner.TokenCurrPos - scanner.TokenStartPos);
  token.Line = scanner.Line;
  token.desc = NULL;
  return token;
}

Token errorToken(const char *str) {
  saveScannerPos(false);

  Token token;
  token.TokenType = TOKEN_ERROR;
  token.OffsetFromStart = (scanner.TokenStartPos - 0);
  token.Line = scanner.Line;
  token.desc = str;
  token.Length = (int)strlen(str);
  return token;
}

void skipNonTokens() {
  while (true) {
    char ch = ReadCharFromFile(scanner.pTokenCurrent);
    switch (ch) {
    case ' ':
    case '\r':
    case '\t':
      updateScanner();
      break;
    case '\n':
      updateScanner();
      increaseScannerLine();
      break;
    case '/': {
      char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
      if (nextCh == '/') {
        while (true) {
          char ignoreCh = ReadCharFromFile(scanner.pTokenCurrent);
          if (ignoreCh == '\n' || ignoreCh == EOF) {
            UnReadLastCharFromFile(ignoreCh, scanner.pTokenCurrent);
            updateScanner();
            break;
          }
        }
      } else {
        UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
        updateScanner();
        UnReadLastCharFromFile(ch, scanner.pTokenCurrent);
        updateScanner();
        return;
      }
      break;
    }
    default:
      UnReadLastCharFromFile(ch, scanner.pTokenCurrent);
      updateScanner();
      return;
    }
  }
}

TokenType checkKeyword(int start, const char *remainingKeyword,
                       TokenType tokenType) {
  saveScannerPos(false);
  TokenType resultTokenType = tokenType;

  int scannedKeywordLen = scanner.TokenCurrPos - scanner.TokenStartPos;
  if ((start + strlen(remainingKeyword)) == scannedKeywordLen) {
    UnReadLastManyCharFromFile(-1 * strlen(remainingKeyword),
                               scanner.pTokenCurrent);
    int tempItr = 0;
    while (tempItr < strlen(remainingKeyword)) {
      char actualCh = ReadCharFromFile(scanner.pTokenCurrent);
      char expectedCh = remainingKeyword[tempItr];
      if (actualCh != expectedCh) {
        resultTokenType = TOKEN_IDENTIFIER;
        break;
      }
      tempItr++;
    }
    tempItr = strlen(remainingKeyword) - tempItr - 1;
    while (tempItr > 0) {
      ReadCharFromFile(scanner.pTokenCurrent);
      tempItr--;
    }
    saveScannerPos(false);
  } else {
    resultTokenType = TOKEN_IDENTIFIER;
  }
  return resultTokenType;
}

Token ScanToken() {
  skipNonTokens();
  saveScannerPos(true);
  char ch = ReadCharFromFile(scanner.pTokenCurrent);
  Token token;

  if (ch >= '0' && ch <= '9') {
    while (true) {
      char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
      if (!(nextCh >= '0' && nextCh <= '9') && !(nextCh == '.')) {
        printf("should be here\n");
        UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
        break;
      }
    }
    token = makeToken(TOKEN_NUMBER);
    updateScanner();
    return token;
  }

  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')) {
    while (true) {
      char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
      if (!(nextCh >= 'a' && nextCh <= 'z') &&
          !(nextCh >= 'A' && nextCh <= 'Z') && !(nextCh == '_') &&
          !(nextCh >= '0' && nextCh <= '9')) {
        UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
        break;
      }
    }
    saveScannerPos(false);

    // some sort of identifier
    switch (ch) {
    case 'a': {
      TokenType tokenType = checkKeyword(1, "nd", TOKEN_AND);
      token = makeToken(tokenType);
      break;
    }
    case 'c': {
      TokenType tokenType = checkKeyword(1, "lass", TOKEN_CLASS);
      token = makeToken(tokenType);
      break;
    }
    case 'e': {
      TokenType tokenType = checkKeyword(1, "lse", TOKEN_ELSE);
      token = makeToken(tokenType);
      break;
    }
    case 'i': {
      TokenType tokenType = checkKeyword(1, "f", TOKEN_IF);
      token = makeToken(tokenType);
      break;
    }
    case 'n': {
      TokenType tokenType = checkKeyword(1, "il", TOKEN_NIL);
      token = makeToken(tokenType);
      break;
    }
    case 'o': {
      TokenType tokenType = checkKeyword(1, "r", TOKEN_OR);
      token = makeToken(tokenType);
      break;
    }
    case 'p': {
      TokenType tokenType = checkKeyword(1, "rint", TOKEN_PRINT);
      token = makeToken(tokenType);
      break;
    }
    case 'r': {
      TokenType tokenType = checkKeyword(1, "eturn", TOKEN_RETURN);
      token = makeToken(tokenType);
      break;
    }
    case 's': {
      TokenType tokenType = checkKeyword(1, "uper", TOKEN_SUPER);
      token = makeToken(tokenType);
      break;
    }
    case 'v': {
      TokenType tokenType = checkKeyword(1, "ar", TOKEN_VAR);
      token = makeToken(tokenType);
      break;
    }
    case 'w': {
      TokenType tokenType = checkKeyword(1, "hile", TOKEN_WHILE);
      token = makeToken(tokenType);
      break;
    }
    case 'f': {
      TokenType tokenTypeFalse = checkKeyword(1, "alse", TOKEN_FALSE);
      if (tokenTypeFalse == TOKEN_FALSE) {
        token = makeToken(tokenTypeFalse);
        break;
      }
      TokenType tokenTypeFor = checkKeyword(1, "or", TOKEN_FOR);
      if (tokenTypeFor == TOKEN_FOR) {
        token = makeToken(tokenTypeFor);
        break;
      }
      TokenType tokenTypeFun = checkKeyword(1, "un", TOKEN_FUN);
      if (tokenTypeFun == TOKEN_FUN) {
        token = makeToken(tokenTypeFun);
        break;
      }
      token = makeToken(TOKEN_IDENTIFIER);
      break;
    }
    case 't': {
      TokenType tokenTypeThis = checkKeyword(1, "his", TOKEN_THIS);
      if (tokenTypeThis == TOKEN_THIS) {
        token = makeToken(tokenTypeThis);
        break;
      }
      TokenType tokenTypeTrue = checkKeyword(1, "rue", TOKEN_TRUE);
      if (tokenTypeTrue == TOKEN_TRUE) {
        token = makeToken(tokenTypeTrue);
        break;
      }
      token = makeToken(TOKEN_IDENTIFIER);
      break;
    }
    default: {
      token = makeToken(TOKEN_IDENTIFIER);
    }
    }
    updateScanner();
    return token;
  }

  switch (ch) {
  case EOF:
    token = makeToken(TOKEN_EOF);
    break;
  case '(':
    token = makeToken(TOKEN_LEFT_PAREN);
    break;
  case ')':
    token = makeToken(TOKEN_RIGHT_PAREN);
    break;
  case '{':
    token = makeToken(TOKEN_LEFT_BRACE);
    break;
  case '}':
    token = makeToken(TOKEN_RIGHT_BRACE);
    break;
  case ',':
    token = makeToken(TOKEN_COMMA);
    break;
  case '.':
    token = makeToken(TOKEN_DOT);
    break;
  case '-':
    token = makeToken(TOKEN_MINUS);
    break;
  case '+':
    token = makeToken(TOKEN_PLUS);
    break;
  case ';':
    token = makeToken(TOKEN_SEMICOLON);
    break;
  case '/':
    token = makeToken(TOKEN_SLASH);
    break;
  case '*':
    token = makeToken(TOKEN_STAR);
    break;
  case '!': {
    char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
    if (nextCh == '=') {
      token = makeToken(TOKEN_BANG_EQUAL);
    } else {
      UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
      token = makeToken(TOKEN_BANG);
    }
    break;
  }
  case '=': {
    char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
    if (nextCh == '=') {
      token = makeToken(TOKEN_EQUAL_EQUAL);
    } else {
      UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
      token = makeToken(TOKEN_EQUAL);
    }
    break;
  }
  case '>': {
    char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
    if (nextCh == '=') {
      token = makeToken(TOKEN_GREATER_EQUAL);
    } else {
      UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
      token = makeToken(TOKEN_GREATER);
    }
    break;
  }
  case '<': {
    char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
    if (nextCh == '=') {
      token = makeToken(TOKEN_LESS_EQUAL);
    } else {
      UnReadLastCharFromFile(nextCh, scanner.pTokenCurrent);
      token = makeToken(TOKEN_LESS);
    }
    break;
  }
  case '"': {
    while (true) {
      char nextCh = ReadCharFromFile(scanner.pTokenCurrent);
      if (nextCh == '"') {
        token = makeToken(TOKEN_STRING);
        break;
      } else if (nextCh == EOF) {
        token = errorToken("EOF encountered without string termination");
        break;
      } else if (nextCh == '\n') {
        increaseScannerLine();
      } else {
        // do nothing
      }
    }
    break;
  }
  default: {
    token = errorToken("Unable to scan the token");
  }
  }

  updateScanner();
  return token;
}

void ResetScanner() {
  CloseFile(scanner.pTokenCurrent);

  scanner.TokenStartPos = -1;
  scanner.TokenCurrPos = -1;
  scanner.pTokenCurrent = NULL;
  scanner.Line = -1;
}
