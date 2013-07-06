//
// Copyright (c) 2013 Caitlin Potter and Contributors
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <TimedText/Node.h>
#include <gtest/gtest.h>
using namespace TimedText;

TEST(VoiceNode,Initialize)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_EQ(InternalNode,node.type());
  EXPECT_EQ(VoiceNode,node.element());
}

TEST(VoiceNode,GetText)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_STREQ("", node.text());
}

TEST(VoiceNode,GetVoice)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_STREQ("", node.voice());
}

TEST(VoiceNode,GetTimestamp)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_EQ(MalformedTimestamp,node.timestamp());
}

TEST(VoiceNode,GetStyleClasses)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_STREQ("", node.styleClasses());
}

TEST(VoiceNode,SetText)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_FALSE(node.setText(String()));
  EXPECT_FALSE(node.setText(String(0)));
  EXPECT_FALSE(node.setText(String("")));
  EXPECT_FALSE(node.setText(String("Meow")));
  EXPECT_STREQ("", node.text());
}

TEST(VoiceNode,SetVoice)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_TRUE(node.setVoice(String()));
  EXPECT_TRUE(node.setVoice(String(0)));
  EXPECT_TRUE(node.setVoice(String("")));
  EXPECT_TRUE(node.setVoice(String("Meow")));
  EXPECT_STREQ("Meow", node.voice());
}

TEST(VoiceNode,SetTimestamp)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_FALSE(node.setTimestamp(MalformedTimestamp));
  EXPECT_FALSE(node.setTimestamp(666.0));
  EXPECT_EQ(MalformedTimestamp, node.timestamp());
}

TEST(VoiceNode,SetStyleClasses)
{
  Node node(InternalNode,VoiceNode);
  EXPECT_TRUE(node.setStyleClasses(String()));
  EXPECT_TRUE(node.setStyleClasses(String(0)));
  EXPECT_TRUE(node.setStyleClasses(String("")));
  EXPECT_TRUE(node.setStyleClasses(String("background-color: #fff; font-family: sans-serif")));
  EXPECT_STREQ("background-color: #fff; font-family: sans-serif", node.styleClasses());
}
