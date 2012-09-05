#include "oauthtokenizer.h"
#include <QStringList>

OAuthTokenizer::OAuthTokenizer(QObject *parent) :
    QObject(parent)
{
}

void OAuthTokenizer::tokenize(QString decoded) {
  QStringList tokens;
  for (;decoded.length()>0;) {
      int i=decoded.indexOf("&");
      if (i>0) {
          tokens.append(decoded.left(i));
          decoded=decoded.right(decoded.length()-i-1);
      } else {
          tokens.append(decoded);
          decoded="";
      }
  }
  QString oauth_tokenString = "oauth_token=";
  QString edam_shardString = "edam_shard=";
  QString edam_userIdString = "edam_userid=";
  QString edam_expiresString = "edam_expires=";
  QString edam_noteStoreUrlString ="edam_notestoreurl=";
  QString edam_webApiUrlPrefixString = "edam_webapiurlprefix=";
  oauth_token = "";
  edam_shard = "";
  edam_userId = "";
  edam_expires = "";
  edam_noteStoreUrl = "";
  edam_webApiUrlPrefix = "";

  for (int i=0; i<tokens.size(); i++) {
      QString token = tokens[i];
      token = token.toLower();
      if (token.startsWith(oauth_tokenString))
          oauth_token = tokens[i].right(token.length()-oauth_tokenString.length());
      if (token.startsWith(edam_shardString))
          edam_shard = tokens[i].right(token.length()-edam_shardString.length());
      if (token.startsWith(edam_userIdString))
          edam_userId = tokens[i].right(token.length()-edam_userIdString.length());
      if (token.startsWith(edam_expiresString))
          edam_expires = tokens[i].right(token.length()-edam_expiresString.length());
      if (token.startsWith(edam_noteStoreUrlString))
          edam_noteStoreUrl = tokens[i].right(token.length()-edam_noteStoreUrlString.length());
      if (token.startsWith(edam_webApiUrlPrefixString))
          edam_webApiUrlPrefix=tokens[i].right(token.length()-edam_webApiUrlPrefixString.length());

  }

}