// Copyright (c) 2016 The Space Game Developers. All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#version 330 core



layout(location = 0) in vec3 vertLocIn;

void main()
{
    gl_Position.xyz = vertLocIn;
    gl_Position.z = 1.f;
}
