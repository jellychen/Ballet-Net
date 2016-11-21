#include "BalHttpMime.h"
using namespace Ballet;
using namespace Protocol;

BalHttpMime::BalHttpMime()
{
    mimePool_["html"]       = "text/html";
    mimePool_["htm"]        = "text/html";
    mimePool_["shtml"]      = "text/html";
    mimePool_["css"]        = "text/css";
    mimePool_["xml"]        = "text/xml";
    mimePool_["gif"]        = "image/gif";
    mimePool_["jpeg"]       = "image/jpeg";
    mimePool_["jpg"]        = "image/jpeg";
    mimePool_["js"]         = "application/x-javascript";
    mimePool_["atom"]       = "application/atom+xml";
    mimePool_["rss"]        = "application/rss+xml";
    mimePool_["mml"]        = "text/mathml";
    mimePool_["txt"]        = "text/plain";
    mimePool_["jad"]        = "text/vnd.sun.j2me.app-descriptor";
    mimePool_["wml"]        = "text/vnd.wap.wml";
    mimePool_["htc"]        = "text/x-component";
    mimePool_["png"]        = "image/png";
    mimePool_["tif"]        = "image/tiff";
    mimePool_["tiff"]       = "image/tiff";
    mimePool_["wbmp"]       = "image/vnd.wap.wbmp";
    mimePool_["ico"]        = "image/x-icon";
    mimePool_["jng"]        = "image/x-jng";
    mimePool_["bmp"]        = "image/x-ms-bmp";
    mimePool_["svg"]        = "image/svg+xml";
    mimePool_["svgz"]       = "image/svg+xml";
    mimePool_["webp"]       = "image/webp";
    mimePool_["jar"]        = "application/java-archive";
    mimePool_["war"]        = "application/java-archive";
    mimePool_["ear"]        = "application/java-archive";
    mimePool_["hqx"]        = "application/mac-binhex40";
    mimePool_["doc"]        = "application/msword";
    mimePool_["pdf"]        = "application/pdf";
    mimePool_["ps"]         = "application/postscript";
    mimePool_["eps"]        = "application/postscript";
    mimePool_["ai"]         = "application/postscript";
    mimePool_["rtf"]        = "application/rtf";
    mimePool_["xls"]        = "application/vnd.ms-excel";
    mimePool_["ppt"]        = "application/vnd.ms-powerpoint";
    mimePool_["wmlc"]       = "application/vnd.wap.wmlc";
    mimePool_["kml"]        = "application/vnd.google-earth.kml+xml";
    mimePool_["kmz"]        = "application/vnd.google-earth.kmz";
    mimePool_["7z"]         = "application/x-7z-compressed";
    mimePool_["cco"]        = "application/x-cocoa";
    mimePool_["jardiff"]    = "application/x-java-archive-diff";
    mimePool_["jnlp"]       = "application/x-java-jnlp-file";
    mimePool_["run"]        = "application/x-makeself";
    mimePool_["pl"]         = "application/x-perl";
    mimePool_["pm"]         = "application/x-perl";
    mimePool_["prc"]        = "application/x-pilot";
    mimePool_["pdb"]        = "application/x-pilot";
    mimePool_["rar"]        = "application/x-rar-compressed";
    mimePool_["rpm"]        = "application/x-redhat-package-manager";
    mimePool_["sea"]        = "application/x-sea";
    mimePool_["swf"]        = "application/x-shockwave-flash";
    mimePool_["sit"]        = "application/x-stuffit";
    mimePool_["tcl"]        = "application/x-tcl";
    mimePool_["tk"]         = "application/x-tcl";
    mimePool_["der"]        = "application/x-x509-ca-cert";
    mimePool_["pem"]        = "application/x-x509-ca-cert";
    mimePool_["crt"]        = "application/x-x509-ca-cert";
    mimePool_["xpi"]        = "application/x-xpinstall";
    mimePool_["xhtml"]      = "application/xhtml+xml";
    mimePool_["zip"]        = "application/zip";
    mimePool_["bin"]        = "application/octet-stream";
    mimePool_["exe"]        = "application/octet-stream";
    mimePool_["dll"]        = "application/octet-stream";
    mimePool_["deb"]        = "application/octet-stream";
    mimePool_["dmg"]        = "application/octet-stream";
    mimePool_["eot"]        = "application/octet-stream";
    mimePool_["iso"]        = "application/octet-stream";
    mimePool_["img"]        = "application/octet-stream";
    mimePool_["msi"]        = "application/octet-stream";
    mimePool_["msp"]        = "application/octet-stream";
    mimePool_["msm"]        = "application/octet-stream";
    mimePool_["mid"]        = "audio/midi";
    mimePool_["midi"]       = "audio/midi";
    mimePool_["kar"]        = "audio/midi";
    mimePool_["mp3"]        = "audio/mpeg";
    mimePool_["ogg"]        = "audio/ogg";
    mimePool_["m4a"]        = "audio/x-m4a";
    mimePool_["ra"]         = "audio/x-realaudio";
    mimePool_["3gpp"]       = "video/3gpp";
    mimePool_["3gp"]        = "video/3gpp";
    mimePool_["mp4"]        = "video/mp4";
    mimePool_["mpeg"]       = "video/mpeg";
    mimePool_["mpg"]        = "video/mpeg";
    mimePool_["mov"]        = "video/quicktime";
    mimePool_["webm"]       = "video/webm";
    mimePool_["flv"]        = "video/x-flv";
    mimePool_["m4v"]        = "video/x-m4v";
    mimePool_["mng"]        = "video/x-mng";
    mimePool_["asx"]        = "video/x-ms-asf";
    mimePool_["asf"]        = "video/x-ms-asf";
    mimePool_["wmv"]        = "video/x-ms-wmv";
    mimePool_["avi"]        = "video/x-msvideo";
}

std::string BalHttpMime::GetMime(const char* type) const
{
    std::string key(type);
    mapMimePoolT::const_iterator iter = mimePool_.find(key);
    if (mimePool_.end() == iter)
    {
        return std::string("");
    }
    return iter->second;
}
