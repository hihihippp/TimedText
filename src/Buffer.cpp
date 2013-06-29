#include <TimedText/Buffer.h>

namespace TimedText
{

Buffer::Buffer(Flags _flags)
  : flags(_flags), final(false), i(0)
{
}

Buffer::~Buffer()
{
}

const char *
Buffer::curr() const
{
  if(i < 0 || i >= buffer.size())
    return "";
  return buffer.text() + i;
}

bool
Buffer::seek(int n, bool abs)
{
  if(!abs)
    n += i;
  if(n < 0 || n >= buffer.size())
    return false;
  i = n;
  return true;
}

void
Buffer::performDiscard(int bytes)
{
  seek(bytes);
}

void
Buffer::discard(int bytes)
{
  if(!bytes)
    return;
  lock();
  performDiscard(bytes);
  unlock();
}

void
Buffer::discard()
{
  int bytes = pos();
  if(!bytes)
    return;
  lock();
  performDiscard(bytes);
  unlock();
}

bool
Buffer::refill(const char utf8[], int count, bool final)
{
  bool result;
  lock();
  this->final = final;
	result = buffer.append(utf8,count);
  unlock();
  return result;
}

int
Buffer::read(char out[], int max)
{
  int ret = max;
  if(ret <= 0)
    return 0;
  lock();
  if(buffer.size() - i < max)
    ret = buffer.size() - i;
  ::memcpy(out, buffer.text() + i, ret);
  unlock();
  return ret;
}

bool
Buffer::next(char &out)
{
  if(i >= buffer.size()) {
    out = '\0';
    return false;
  }
  out = buffer.text()[i++];
  return true;
}

bool
Buffer::collectWord(String &result, int *len)
{
  if(eof())
    return false;
  // This is a fairly generous buffer, which well
  // exceeds the requirements of WebVTT
  char tmp[0x80] = "";
  int n = 0;
  char c;
  bool finished = false;

retry:
  lock();
  while(n < sizeof(tmp) && next(c)) {
    if(!Char::isHtml5Space(c))
      tmp[n++] = c;
    else {
      --i;
      finished = true;
      break;
    }
  }
  unlock();

  if(n >= sizeof(tmp) || eof())
    finished = true;

  if(!finished && isAsynchronous()) {
    sleep();
    goto retry;
  }

  result += String(tmp,n);
  if(len)
    *len = n;
  return finished;
}

bool
Buffer::collectDigits(String &result, int *len)
{
  if(eof())
    return false;
  // This is way generous for a series of digits.
  // StringBuilder might be a little bit expensive to
  // use for this
  char tmp[0x40] = "";
  int n = 0;
  char c;
  bool finished = false;

retry:
  lock();
  while(n < sizeof(tmp) && next(c)) {
    if(Char::isAsciiDigit(c))
      tmp[n++] = c;
    else {
      --i;
      finished = true;
      break;
    }
  }
  unlock();

  if(n >= sizeof(tmp) || eof())
    finished = true;

  if(!finished && isAsynchronous()) {
    sleep();
    goto retry;
  }

  result += String(tmp,n);
  if(len)
    *len = n;
  return finished;
}

bool
Buffer::skipWhitespace(int *len)
{
  if(eof())
    return false;
  int n = 0;
  char c;
  bool finished = false;

retry:
  lock();
  while(next(c)) {
    if(Char::isHtml5Space(c))
      ++n;
    else {
      --i;
      finished = true;
      break;
    }
  }
  unlock();

  if(eof())
    finished = true;

  if(!finished && isAsynchronous()) {
    sleep();
    goto retry;
  }

  if(len)
    *len = n;
  return finished;
}

} // TimedText
