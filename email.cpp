#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>
#include <string>
using namespace std;

#define FROM    "<svetlio1994@gmail.com>"
#define TO      "<example@gmail.com>"
 
char *payload_text[] = {
  "To: " TO "\r\n",
  "From: " FROM "\r\n",
  "Subject: Important mail from social network\r\n",
  "texthj,vbjhbhj,bjhk,bkjbnkjnjknbkjbk\r\n",
  NULL
};
 
struct upload_status {
  int lines_read;
};
 
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  const char *data;
 
  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }
 
  data = payload_text[upload_ctx->lines_read];
 
  if(data) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;
 
    return len;
  }
 
  return 0;
}


void sendEmail(string _to, string _message)
{
  
  string to = "To: <" +_to+ ">\r\n";
 
  char* b = new char[to.length()];
  strcpy(b,to.c_str());


  string message = _message+"\r\n";
  char* a = new char[message.length()];
  strcpy(a,message.c_str());

  payload_text[3]=a;
  payload_text[0]=b;




  CURL *curl;
  CURLcode res = CURLE_OK;
  struct curl_slist *recipients = NULL;
  struct upload_status upload_ctx;
 
  upload_ctx.lines_read = 0;
 
 
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_USERNAME, "svetlio1994@gmail.com");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "");
    curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_CAINFO, "google.pem");
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
    recipients = curl_slist_append(recipients, _to.c_str());
    //curl_easy_setopt(curl, CURLOPT_FILE, "edgE0DF.tmp"); 
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    curl_slist_free_all(recipients);
 
    curl_easy_cleanup(curl);
  }

}
