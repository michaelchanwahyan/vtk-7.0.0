/*=========================================================================

  Program:   Visualization Toolkit
  Module:    TestRenderView.cxx

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/*-------------------------------------------------------------------------
  Copyright 2008 Sandia Corporation.
  Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
  the U.S. Government retains certain rights in this software.
-------------------------------------------------------------------------*/

#include "vtkAnnotationLink.h"
#include "vtkCommand.h"
#include "vtkCubeSource.h"
#include "vtkInteractorEventRecorder.h"
#include "vtkRenderedSurfaceRepresentation.h"
#include "vtkRenderView.h"
#include "vtkRegressionTestImage.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkSphereSource.h"
#include "vtkTestUtilities.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"

#include <vector>

#include "vtkSmartPointer.h"
#define VTK_CREATE(type, name) \
  vtkSmartPointer<type> name = vtkSmartPointer<type>::New()

class TestRenderViewUpdater : public vtkCommand
{
public:
  static TestRenderViewUpdater* New()
  { return new TestRenderViewUpdater; }

  void AddView(vtkView* view)
  {
    this->Views.push_back(view);
    view->AddObserver(vtkCommand::SelectionChangedEvent, this);
  }

  virtual void Execute(vtkObject*, unsigned long, void*)
  {
    for (unsigned int i = 0; i < this->Views.size(); i++)
      {
      this->Views[i]->Update();
      }
  }
private:
  TestRenderViewUpdater() { }
  ~TestRenderViewUpdater() { }
  std::vector<vtkView*> Views;
};

static char RenderViewEventLog[] =
"# StreamVersion 1\n"
"RenderEvent 0 0 0 0 0 0 0\n"
"EnterEvent 299 49 0 0 0 0 0\n"
"MouseMoveEvent 299 49 0 0 0 0 0\n"
"MouseMoveEvent 294 52 0 0 0 0 0\n"
"MouseMoveEvent 289 54 0 0 0 0 0\n"
"MouseMoveEvent 283 56 0 0 0 0 0\n"
"MouseMoveEvent 278 59 0 0 0 0 0\n"
"MouseMoveEvent 274 62 0 0 0 0 0\n"
"MouseMoveEvent 269 64 0 0 0 0 0\n"
"MouseMoveEvent 265 67 0 0 0 0 0\n"
"MouseMoveEvent 262 68 0 0 0 0 0\n"
"MouseMoveEvent 260 69 0 0 0 0 0\n"
"MouseMoveEvent 259 70 0 0 0 0 0\n"
"MouseMoveEvent 257 70 0 0 0 0 0\n"
"MouseMoveEvent 254 71 0 0 0 0 0\n"
"MouseMoveEvent 254 70 0 0 0 0 0\n"
"MouseMoveEvent 250 74 0 0 0 0 0\n"
"MouseMoveEvent 247 78 0 0 0 0 0\n"
"MouseMoveEvent 245 80 0 0 0 0 0\n"
"MouseMoveEvent 245 83 0 0 0 0 0\n"
"MouseMoveEvent 245 84 0 0 0 0 0\n"
"MouseMoveEvent 245 86 0 0 0 0 0\n"
"MouseMoveEvent 244 88 0 0 0 0 0\n"
"MouseMoveEvent 244 90 0 0 0 0 0\n"
"MouseMoveEvent 243 93 0 0 0 0 0\n"
"MouseMoveEvent 241 97 0 0 0 0 0\n"
"MouseMoveEvent 238 100 0 0 0 0 0\n"
"MouseMoveEvent 237 106 0 0 0 0 0\n"
"MouseMoveEvent 235 111 0 0 0 0 0\n"
"MouseMoveEvent 234 115 0 0 0 0 0\n"
"MouseMoveEvent 232 119 0 0 0 0 0\n"
"MouseMoveEvent 231 124 0 0 0 0 0\n"
"MouseMoveEvent 230 127 0 0 0 0 0\n"
"MouseMoveEvent 229 133 0 0 0 0 0\n"
"MouseMoveEvent 229 136 0 0 0 0 0\n"
"MouseMoveEvent 228 139 0 0 0 0 0\n"
"MouseMoveEvent 226 143 0 0 0 0 0\n"
"MouseMoveEvent 225 148 0 0 0 0 0\n"
"MouseMoveEvent 224 151 0 0 0 0 0\n"
"MouseMoveEvent 224 154 0 0 0 0 0\n"
"MouseMoveEvent 224 157 0 0 0 0 0\n"
"MouseMoveEvent 224 160 0 0 0 0 0\n"
"MouseMoveEvent 224 162 0 0 0 0 0\n"
"MouseMoveEvent 224 163 0 0 0 0 0\n"
"MouseMoveEvent 224 165 0 0 0 0 0\n"
"MouseMoveEvent 224 166 0 0 0 0 0\n"
"MouseMoveEvent 224 167 0 0 0 0 0\n"
"MouseMoveEvent 224 169 0 0 0 0 0\n"
"MouseMoveEvent 223 170 0 0 0 0 0\n"
"MouseMoveEvent 222 172 0 0 0 0 0\n"
"MouseMoveEvent 221 175 0 0 0 0 0\n"
"MouseMoveEvent 220 178 0 0 0 0 0\n"
"MouseMoveEvent 219 180 0 0 0 0 0\n"
"MouseMoveEvent 218 183 0 0 0 0 0\n"
"MouseMoveEvent 218 185 0 0 0 0 0\n"
"MouseMoveEvent 218 187 0 0 0 0 0\n"
"MouseMoveEvent 217 188 0 0 0 0 0\n"
"MouseMoveEvent 217 190 0 0 0 0 0\n"
"MouseMoveEvent 216 191 0 0 0 0 0\n"
"MouseMoveEvent 215 192 0 0 0 0 0\n"
"LeftButtonPressEvent 215 192 0 0 0 0 0\n"
"StartInteractionEvent 215 192 0 0 0 0 0\n"
"MouseMoveEvent 213 192 0 0 0 0 0\n"
"MouseMoveEvent 213 191 0 0 0 0 0\n"
"MouseMoveEvent 210 190 0 0 0 0 0\n"
"MouseMoveEvent 209 190 0 0 0 0 0\n"
"MouseMoveEvent 208 188 0 0 0 0 0\n"
"MouseMoveEvent 204 187 0 0 0 0 0\n"
"MouseMoveEvent 202 185 0 0 0 0 0\n"
"MouseMoveEvent 200 184 0 0 0 0 0\n"
"MouseMoveEvent 198 181 0 0 0 0 0\n"
"MouseMoveEvent 195 181 0 0 0 0 0\n"
"MouseMoveEvent 194 179 0 0 0 0 0\n"
"MouseMoveEvent 193 179 0 0 0 0 0\n"
"MouseMoveEvent 191 177 0 0 0 0 0\n"
"MouseMoveEvent 190 176 0 0 0 0 0\n"
"MouseMoveEvent 189 176 0 0 0 0 0\n"
"MouseMoveEvent 189 175 0 0 0 0 0\n"
"MouseMoveEvent 187 174 0 0 0 0 0\n"
"MouseMoveEvent 187 173 0 0 0 0 0\n"
"MouseMoveEvent 186 172 0 0 0 0 0\n"
"MouseMoveEvent 184 171 0 0 0 0 0\n"
"MouseMoveEvent 183 170 0 0 0 0 0\n"
"MouseMoveEvent 181 169 0 0 0 0 0\n"
"MouseMoveEvent 179 167 0 0 0 0 0\n"
"MouseMoveEvent 178 166 0 0 0 0 0\n"
"MouseMoveEvent 176 165 0 0 0 0 0\n"
"MouseMoveEvent 175 164 0 0 0 0 0\n"
"MouseMoveEvent 174 163 0 0 0 0 0\n"
"MouseMoveEvent 172 162 0 0 0 0 0\n"
"MouseMoveEvent 170 161 0 0 0 0 0\n"
"MouseMoveEvent 169 160 0 0 0 0 0\n"
"MouseMoveEvent 166 158 0 0 0 0 0\n"
"MouseMoveEvent 164 156 0 0 0 0 0\n"
"MouseMoveEvent 162 155 0 0 0 0 0\n"
"MouseMoveEvent 160 153 0 0 0 0 0\n"
"MouseMoveEvent 156 151 0 0 0 0 0\n"
"MouseMoveEvent 153 148 0 0 0 0 0\n"
"MouseMoveEvent 150 147 0 0 0 0 0\n"
"MouseMoveEvent 147 145 0 0 0 0 0\n"
"MouseMoveEvent 145 144 0 0 0 0 0\n"
"MouseMoveEvent 143 143 0 0 0 0 0\n"
"MouseMoveEvent 141 142 0 0 0 0 0\n"
"MouseMoveEvent 139 142 0 0 0 0 0\n"
"MouseMoveEvent 139 141 0 0 0 0 0\n"
"LeftButtonReleaseEvent 139 141 0 0 0 0 0\n"
"EndInteractionEvent 139 141 0 0 0 0 0\n"
"MouseMoveEvent 139 141 0 0 0 0 0\n"
"MouseMoveEvent 138 140 0 0 0 0 0\n"
"MouseMoveEvent 137 140 0 0 0 0 0\n"
"MouseMoveEvent 136 140 0 0 0 0 0\n"
"MouseMoveEvent 135 140 0 0 0 0 0\n"
"MouseMoveEvent 134 140 0 0 0 0 0\n"
"MouseMoveEvent 133 140 0 0 0 0 0\n"
"MouseMoveEvent 130 140 0 0 0 0 0\n"
"MouseMoveEvent 127 141 0 0 0 0 0\n"
"MouseMoveEvent 122 143 0 0 0 0 0\n"
"MouseMoveEvent 116 146 0 0 0 0 0\n"
"MouseMoveEvent 110 149 0 0 0 0 0\n"
"MouseMoveEvent 103 152 0 0 0 0 0\n"
"MouseMoveEvent 97 155 0 0 0 0 0\n"
"MouseMoveEvent 91 158 0 0 0 0 0\n"
"MouseMoveEvent 85 161 0 0 0 0 0\n"
"MouseMoveEvent 82 163 0 0 0 0 0\n"
"MouseMoveEvent 78 166 0 0 0 0 0\n"
"MouseMoveEvent 77 168 0 0 0 0 0\n"
"MouseMoveEvent 76 169 0 0 0 0 0\n"
"MouseMoveEvent 76 170 0 0 0 0 0\n"
"MouseMoveEvent 75 171 0 0 0 0 0\n"
"MouseMoveEvent 75 172 0 0 0 0 0\n"
"MouseMoveEvent 74 173 0 0 0 0 0\n"
"MouseMoveEvent 73 175 0 0 0 0 0\n"
"MouseMoveEvent 72 176 0 0 0 0 0\n"
"MouseMoveEvent 70 178 0 0 0 0 0\n"
"MouseMoveEvent 68 179 0 0 0 0 0\n"
"MouseMoveEvent 67 180 0 0 0 0 0\n"
"MouseMoveEvent 66 181 0 0 0 0 0\n"
"MouseMoveEvent 65 182 0 0 0 0 0\n"
"LeftButtonPressEvent 65 182 0 0 0 0 0\n"
"StartInteractionEvent 65 182 0 0 0 0 0\n"
"MouseMoveEvent 65 181 0 0 0 0 0\n"
"MouseMoveEvent 66 180 0 0 0 0 0\n"
"MouseMoveEvent 67 178 0 0 0 0 0\n"
"MouseMoveEvent 67 175 0 0 0 0 0\n"
"MouseMoveEvent 69 174 0 0 0 0 0\n"
"MouseMoveEvent 70 172 0 0 0 0 0\n"
"MouseMoveEvent 72 170 0 0 0 0 0\n"
"MouseMoveEvent 73 167 0 0 0 0 0\n"
"MouseMoveEvent 75 166 0 0 0 0 0\n"
"MouseMoveEvent 76 164 0 0 0 0 0\n"
"MouseMoveEvent 78 163 0 0 0 0 0\n"
"MouseMoveEvent 79 162 0 0 0 0 0\n"
"MouseMoveEvent 81 162 0 0 0 0 0\n"
"MouseMoveEvent 83 160 0 0 0 0 0\n"
"MouseMoveEvent 84 160 0 0 0 0 0\n"
"MouseMoveEvent 84 159 0 0 0 0 0\n"
"MouseMoveEvent 86 159 0 0 0 0 0\n"
"MouseMoveEvent 88 158 0 0 0 0 0\n"
"MouseMoveEvent 88 156 0 0 0 0 0\n"
"MouseMoveEvent 89 156 0 0 0 0 0\n"
"MouseMoveEvent 89 155 0 0 0 0 0\n"
"MouseMoveEvent 90 154 0 0 0 0 0\n"
"MouseMoveEvent 91 153 0 0 0 0 0\n"
"LeftButtonReleaseEvent 91 153 0 0 0 0 0\n"
"EndInteractionEvent 91 153 0 0 0 0 0\n"
"MouseMoveEvent 91 153 0 0 0 0 0\n"
"MouseMoveEvent 91 152 0 0 0 0 0\n"
"MouseMoveEvent 91 151 0 0 0 0 0\n"
"MouseMoveEvent 90 150 0 0 0 0 0\n"
"MouseMoveEvent 89 149 0 0 0 0 0\n"
"MouseMoveEvent 88 148 0 0 0 0 0\n"
"MouseMoveEvent 87 146 0 0 0 0 0\n"
"MouseMoveEvent 86 145 0 0 0 0 0\n"
"MouseMoveEvent 85 143 0 0 0 0 0\n"
"MouseMoveEvent 84 142 0 0 0 0 0\n"
"MouseMoveEvent 83 141 0 0 0 0 0\n"
"MouseMoveEvent 83 140 0 0 0 0 0\n"
"MouseMoveEvent 82 140 0 0 0 0 0\n"
"MouseMoveEvent 82 139 0 0 0 0 0\n"
"MouseMoveEvent 81 138 0 0 0 0 0\n"
"MouseMoveEvent 80 136 0 0 0 0 0\n"
"MouseMoveEvent 79 136 0 0 0 0 0\n"
"MouseMoveEvent 78 136 0 0 0 0 0\n"
"MouseMoveEvent 77 136 0 0 0 0 0\n"
"MouseMoveEvent 76 136 0 0 0 0 0\n"
"MouseMoveEvent 75 137 0 0 0 0 0\n"
"MouseMoveEvent 74 138 0 0 0 0 0\n"
"MouseMoveEvent 73 141 0 0 0 0 0\n"
"MouseMoveEvent 71 143 0 0 0 0 0\n"
"MouseMoveEvent 70 146 0 0 0 0 0\n"
"MouseMoveEvent 69 149 0 0 0 0 0\n"
"MouseMoveEvent 68 152 0 0 0 0 0\n"
"MouseMoveEvent 67 155 0 0 0 0 0\n"
"MouseMoveEvent 67 158 0 0 0 0 0\n"
"MouseMoveEvent 66 161 0 0 0 0 0\n"
"MouseMoveEvent 65 164 0 0 0 0 0\n"
"MouseMoveEvent 65 166 0 0 0 0 0\n"
"MouseMoveEvent 65 167 0 0 0 0 0\n"
"MouseMoveEvent 65 168 0 0 0 0 0\n"
"MouseMoveEvent 65 170 0 0 0 0 0\n"
"MouseMoveEvent 65 172 0 0 0 0 0\n"
"MouseMoveEvent 65 174 0 0 0 0 0\n"
"MouseMoveEvent 65 175 0 0 0 0 0\n"
"MouseMoveEvent 64 177 0 0 0 0 0\n"
"MouseMoveEvent 63 179 0 0 0 0 0\n"
"MouseMoveEvent 62 180 0 0 0 0 0\n"
"MouseMoveEvent 61 182 0 0 0 0 0\n"
"MouseMoveEvent 60 183 0 0 0 0 0\n"
"MouseMoveEvent 60 184 0 0 0 0 0\n"
"MouseMoveEvent 59 186 0 0 0 0 0\n"
"MouseMoveEvent 58 187 0 0 0 0 0\n"
"MouseMoveEvent 57 189 0 0 0 0 0\n"
"MouseMoveEvent 56 191 0 0 0 0 0\n"
"MouseMoveEvent 55 192 0 0 0 0 0\n"
"MouseMoveEvent 52 194 0 0 0 0 0\n"
"MouseMoveEvent 51 195 0 0 0 0 0\n"
"MouseMoveEvent 50 196 0 0 0 0 0\n"
"MouseMoveEvent 48 198 0 0 0 0 0\n"
"MouseMoveEvent 47 199 0 0 0 0 0\n"
"MouseMoveEvent 45 200 0 0 0 0 0\n"
"MouseMoveEvent 44 201 0 0 0 0 0\n"
"MouseMoveEvent 43 202 0 0 0 0 0\n"
"MouseMoveEvent 42 203 0 0 0 0 0\n"
"MouseMoveEvent 41 204 0 0 0 0 0\n"
"MouseMoveEvent 41 205 0 0 0 0 0\n"
"MouseMoveEvent 40 206 0 0 0 0 0\n"
"MouseMoveEvent 40 207 0 0 0 0 0\n"
"MouseMoveEvent 39 207 0 0 0 0 0\n"
"MouseMoveEvent 39 208 0 0 0 0 0\n"
"MouseMoveEvent 39 209 0 0 0 0 0\n"
"LeftButtonPressEvent 39 190 0 0 0 0 0\n"
"StartInteractionEvent 39 190 0 0 0 0 0\n"
"MouseMoveEvent 40 190 0 0 0 0 0\n"
"MouseMoveEvent 42 190 0 0 0 0 0\n"
"MouseMoveEvent 45 190 0 0 0 0 0\n"
"MouseMoveEvent 50 190 0 0 0 0 0\n"
"MouseMoveEvent 55 190 0 0 0 0 0\n"
"MouseMoveEvent 62 186 0 0 0 0 0\n"
"MouseMoveEvent 68 181 0 0 0 0 0\n"
"MouseMoveEvent 78 174 0 0 0 0 0\n"
"MouseMoveEvent 87 169 0 0 0 0 0\n"
"MouseMoveEvent 96 163 0 0 0 0 0\n"
"MouseMoveEvent 106 159 0 0 0 0 0\n"
"MouseMoveEvent 116 154 0 0 0 0 0\n"
"MouseMoveEvent 127 149 0 0 0 0 0\n"
"MouseMoveEvent 137 145 0 0 0 0 0\n"
"MouseMoveEvent 146 141 0 0 0 0 0\n"
"MouseMoveEvent 155 136 0 0 0 0 0\n"
"MouseMoveEvent 162 132 0 0 0 0 0\n"
"MouseMoveEvent 169 129 0 0 0 0 0\n"
"MouseMoveEvent 177 125 0 0 0 0 0\n"
"MouseMoveEvent 184 121 0 0 0 0 0\n"
"MouseMoveEvent 190 117 0 0 0 0 0\n"
"MouseMoveEvent 195 113 0 0 0 0 0\n"
"MouseMoveEvent 198 110 0 0 0 0 0\n"
"MouseMoveEvent 203 108 0 0 0 0 0\n"
"MouseMoveEvent 206 105 0 0 0 0 0\n"
"MouseMoveEvent 210 101 0 0 0 0 0\n"
"MouseMoveEvent 216 97 0 0 0 0 0\n"
"MouseMoveEvent 222 93 0 0 0 0 0\n"
"MouseMoveEvent 228 89 0 0 0 0 0\n"
"MouseMoveEvent 234 86 0 0 0 0 0\n"
"MouseMoveEvent 240 82 0 0 0 0 0\n"
"MouseMoveEvent 243 81 0 0 0 0 0\n"
"MouseMoveEvent 245 79 0 0 0 0 0\n"
"LeftButtonReleaseEvent 245 79 0 0 0 0 0\n"
"EndInteractionEvent 245 79 0 0 0 0 0\n"
"MouseMoveEvent 244 79 0 0 0 0 0\n"
"MouseMoveEvent 243 79 0 0 0 0 0\n"
"MouseMoveEvent 242 79 0 0 0 0 0\n"
"MouseMoveEvent 241 79 0 0 0 0 0\n"
"MouseMoveEvent 240 80 0 0 0 0 0\n"
"MouseMoveEvent 238 80 0 0 0 0 0\n"
"MouseMoveEvent 235 81 0 0 0 0 0\n"
"MouseMoveEvent 231 83 0 0 0 0 0\n"
"MouseMoveEvent 227 84 0 0 0 0 0\n"
"MouseMoveEvent 220 87 0 0 0 0 0\n"
"MouseMoveEvent 211 90 0 0 0 0 0\n"
"MouseMoveEvent 203 93 0 0 0 0 0\n"
"MouseMoveEvent 194 97 0 0 0 0 0\n"
"MouseMoveEvent 187 100 0 0 0 0 0\n"
"MouseMoveEvent 181 104 0 0 0 0 0\n"
"MouseMoveEvent 176 107 0 0 0 0 0\n"
"MouseMoveEvent 172 109 0 0 0 0 0\n"
"MouseMoveEvent 170 111 0 0 0 0 0\n"
"MouseMoveEvent 168 112 0 0 0 0 0\n"
"MouseMoveEvent 168 113 0 0 0 0 0\n"
"MouseMoveEvent 168 115 0 0 0 0 0\n"
"MouseMoveEvent 168 115 0 0 0 0 0\n"
"MouseMoveEvent 167 116 0 0 0 0 0\n"
"MouseMoveEvent 165 117 0 0 0 0 0\n"
"MouseMoveEvent 165 120 0 0 0 0 0\n"
"MouseMoveEvent 164 121 0 0 0 0 0\n"
"MouseMoveEvent 163 122 0 0 0 0 0\n"
"MouseMoveEvent 163 124 0 0 0 0 0\n"
"MouseMoveEvent 162 125 0 0 0 0 0\n"
"MouseMoveEvent 161 127 0 0 0 0 0\n"
"MouseMoveEvent 160 129 0 0 0 0 0\n"
"MouseMoveEvent 160 130 0 0 0 0 0\n"
"MouseMoveEvent 160 131 0 0 0 0 0\n"
"MouseMoveEvent 160 132 0 0 0 0 0\n"
"MouseMoveEvent 160 133 0 0 0 0 0\n"
"MouseMoveEvent 160 135 0 0 0 0 0\n"
"MouseMoveEvent 160 137 0 0 0 0 0\n"
"MouseMoveEvent 161 138 0 0 0 0 0\n"
"MouseMoveEvent 162 140 0 0 0 0 0\n"
"MouseMoveEvent 162 143 0 0 0 0 0\n"
"MouseMoveEvent 162 146 0 0 0 0 0\n"
"MouseMoveEvent 162 148 0 0 0 0 0\n"
"MouseMoveEvent 162 150 0 0 0 0 0\n"
"MouseMoveEvent 162 152 0 0 0 0 0\n"
"MouseMoveEvent 162 153 0 0 0 0 0\n"
"MouseMoveEvent 162 156 0 0 0 0 0\n"
"MouseMoveEvent 163 157 0 0 0 0 0\n"
"MouseMoveEvent 164 158 0 0 0 0 0\n"
"MouseMoveEvent 165 160 0 0 0 0 0\n"
"MouseMoveEvent 166 160 0 0 0 0 0\n"
"MouseMoveEvent 168 162 0 0 0 0 0\n"
"MouseMoveEvent 170 163 0 0 0 0 0\n"
"MouseMoveEvent 171 164 0 0 0 0 0\n"
"MouseMoveEvent 171 165 0 0 0 0 0\n"
"MouseMoveEvent 172 166 0 0 0 0 0\n"
"MouseMoveEvent 172 167 0 0 0 0 0\n"
"MouseMoveEvent 172 168 0 0 0 0 0\n"
"MouseMoveEvent 172 170 0 0 0 0 0\n"
"MouseMoveEvent 172 172 0 0 0 0 0\n"
"MouseMoveEvent 172 173 0 0 0 0 0\n"
"MouseMoveEvent 172 174 0 0 0 0 0\n"
"MouseMoveEvent 172 176 0 0 0 0 0\n"
"MouseMoveEvent 172 178 0 0 0 0 0\n"
"MouseMoveEvent 172 179 0 0 0 0 0\n"
"MouseMoveEvent 172 180 0 0 0 0 0\n"
"MouseMoveEvent 172 182 0 0 0 0 0\n"
"MouseMoveEvent 173 182 0 0 0 0 0\n"
"MouseMoveEvent 173 183 0 0 0 0 0\n"
"MouseMoveEvent 174 184 0 0 0 0 0\n"
"MouseMoveEvent 175 185 0 0 0 0 0\n"
"MouseMoveEvent 175 186 0 0 0 0 0\n"
"MouseMoveEvent 176 186 0 0 0 0 0\n"
"MiddleButtonPressEvent 176 186 0 0 0 0 0\n"
"StartInteractionEvent 176 186 0 0 0 0 0\n"
"MouseMoveEvent 175 186 0 0 0 0 0\n"
"RenderEvent 175 186 0 0 0 0 0\n"
"MouseMoveEvent 174 186 0 0 0 0 0\n"
"RenderEvent 174 186 0 0 0 0 0\n"
"MouseMoveEvent 172 185 0 0 0 0 0\n"
"RenderEvent 172 185 0 0 0 0 0\n"
"MouseMoveEvent 171 185 0 0 0 0 0\n"
"RenderEvent 171 185 0 0 0 0 0\n"
"MouseMoveEvent 170 184 0 0 0 0 0\n"
"RenderEvent 170 184 0 0 0 0 0\n"
"MouseMoveEvent 168 182 0 0 0 0 0\n"
"RenderEvent 168 182 0 0 0 0 0\n"
"MouseMoveEvent 167 182 0 0 0 0 0\n"
"RenderEvent 167 182 0 0 0 0 0\n"
"MouseMoveEvent 165 181 0 0 0 0 0\n"
"RenderEvent 165 181 0 0 0 0 0\n"
"MouseMoveEvent 163 180 0 0 0 0 0\n"
"RenderEvent 163 180 0 0 0 0 0\n"
"MouseMoveEvent 162 178 0 0 0 0 0\n"
"RenderEvent 162 178 0 0 0 0 0\n"
"MouseMoveEvent 160 177 0 0 0 0 0\n"
"RenderEvent 160 177 0 0 0 0 0\n"
"MouseMoveEvent 157 176 0 0 0 0 0\n"
"RenderEvent 157 176 0 0 0 0 0\n"
"MouseMoveEvent 154 174 0 0 0 0 0\n"
"RenderEvent 154 174 0 0 0 0 0\n"
"MouseMoveEvent 152 174 0 0 0 0 0\n"
"RenderEvent 152 174 0 0 0 0 0\n"
"MouseMoveEvent 150 172 0 0 0 0 0\n"
"RenderEvent 150 172 0 0 0 0 0\n"
"MouseMoveEvent 148 171 0 0 0 0 0\n"
"RenderEvent 148 171 0 0 0 0 0\n"
"MouseMoveEvent 146 170 0 0 0 0 0\n"
"RenderEvent 146 170 0 0 0 0 0\n"
"MouseMoveEvent 144 168 0 0 0 0 0\n"
"RenderEvent 144 168 0 0 0 0 0\n"
"MouseMoveEvent 142 168 0 0 0 0 0\n"
"RenderEvent 142 168 0 0 0 0 0\n"
"MouseMoveEvent 140 166 0 0 0 0 0\n"
"RenderEvent 140 166 0 0 0 0 0\n"
"MouseMoveEvent 138 165 0 0 0 0 0\n"
"RenderEvent 138 165 0 0 0 0 0\n"
"MouseMoveEvent 136 163 0 0 0 0 0\n"
"RenderEvent 136 163 0 0 0 0 0\n"
"MouseMoveEvent 134 163 0 0 0 0 0\n"
"RenderEvent 134 163 0 0 0 0 0\n"
"MouseMoveEvent 131 161 0 0 0 0 0\n"
"RenderEvent 131 161 0 0 0 0 0\n"
"MouseMoveEvent 130 160 0 0 0 0 0\n"
"RenderEvent 130 160 0 0 0 0 0\n"
"MouseMoveEvent 128 159 0 0 0 0 0\n"
"RenderEvent 128 159 0 0 0 0 0\n"
"MouseMoveEvent 127 159 0 0 0 0 0\n"
"RenderEvent 127 159 0 0 0 0 0\n"
"MouseMoveEvent 126 159 0 0 0 0 0\n"
"RenderEvent 126 159 0 0 0 0 0\n"
"MouseMoveEvent 125 158 0 0 0 0 0\n"
"RenderEvent 125 158 0 0 0 0 0\n"
"MouseMoveEvent 124 158 0 0 0 0 0\n"
"RenderEvent 124 158 0 0 0 0 0\n"
"MouseMoveEvent 123 157 0 0 0 0 0\n"
"RenderEvent 123 157 0 0 0 0 0\n"
"MouseMoveEvent 122 157 0 0 0 0 0\n"
"RenderEvent 122 157 0 0 0 0 0\n"
"MouseMoveEvent 122 156 0 0 0 0 0\n"
"RenderEvent 122 156 0 0 0 0 0\n"
"MouseMoveEvent 121 156 0 0 0 0 0\n"
"RenderEvent 121 156 0 0 0 0 0\n"
"MouseMoveEvent 122 156 0 0 0 0 0\n"
"RenderEvent 122 156 0 0 0 0 0\n"
"MouseMoveEvent 123 157 0 0 0 0 0\n"
"RenderEvent 123 157 0 0 0 0 0\n"
"MouseMoveEvent 124 158 0 0 0 0 0\n"
"RenderEvent 124 158 0 0 0 0 0\n"
"MouseMoveEvent 126 159 0 0 0 0 0\n"
"RenderEvent 126 159 0 0 0 0 0\n"
"MouseMoveEvent 128 159 0 0 0 0 0\n"
"RenderEvent 128 159 0 0 0 0 0\n"
"MouseMoveEvent 130 160 0 0 0 0 0\n"
"RenderEvent 130 160 0 0 0 0 0\n"
"MouseMoveEvent 132 161 0 0 0 0 0\n"
"RenderEvent 132 161 0 0 0 0 0\n"
"MouseMoveEvent 135 162 0 0 0 0 0\n"
"RenderEvent 135 162 0 0 0 0 0\n"
"MouseMoveEvent 138 163 0 0 0 0 0\n"
"RenderEvent 138 163 0 0 0 0 0\n"
"MouseMoveEvent 140 164 0 0 0 0 0\n"
"RenderEvent 140 164 0 0 0 0 0\n"
"MouseMoveEvent 142 165 0 0 0 0 0\n"
"RenderEvent 142 165 0 0 0 0 0\n"
"MouseMoveEvent 144 167 0 0 0 0 0\n"
"RenderEvent 144 167 0 0 0 0 0\n"
"MouseMoveEvent 145 167 0 0 0 0 0\n"
"RenderEvent 145 167 0 0 0 0 0\n"
"MouseMoveEvent 146 168 0 0 0 0 0\n"
"RenderEvent 146 168 0 0 0 0 0\n"
"MouseMoveEvent 147 169 0 0 0 0 0\n"
"RenderEvent 147 169 0 0 0 0 0\n"
"MouseMoveEvent 149 171 0 0 0 0 0\n"
"RenderEvent 149 171 0 0 0 0 0\n"
"MouseMoveEvent 151 172 0 0 0 0 0\n"
"RenderEvent 151 172 0 0 0 0 0\n"
"MouseMoveEvent 154 174 0 0 0 0 0\n"
"RenderEvent 154 174 0 0 0 0 0\n"
"MouseMoveEvent 158 175 0 0 0 0 0\n"
"RenderEvent 158 175 0 0 0 0 0\n"
"MouseMoveEvent 161 177 0 0 0 0 0\n"
"RenderEvent 161 177 0 0 0 0 0\n"
"MouseMoveEvent 163 179 0 0 0 0 0\n"
"RenderEvent 163 179 0 0 0 0 0\n"
"MouseMoveEvent 167 181 0 0 0 0 0\n"
"RenderEvent 167 181 0 0 0 0 0\n"
"MouseMoveEvent 170 183 0 0 0 0 0\n"
"RenderEvent 170 183 0 0 0 0 0\n"
"MouseMoveEvent 173 184 0 0 0 0 0\n"
"RenderEvent 173 184 0 0 0 0 0\n"
"MouseMoveEvent 175 187 0 0 0 0 0\n"
"RenderEvent 175 187 0 0 0 0 0\n"
"MouseMoveEvent 177 188 0 0 0 0 0\n"
"RenderEvent 177 188 0 0 0 0 0\n"
"MouseMoveEvent 180 190 0 0 0 0 0\n"
"RenderEvent 180 190 0 0 0 0 0\n"
"MouseMoveEvent 181 191 0 0 0 0 0\n"
"RenderEvent 181 191 0 0 0 0 0\n"
"MouseMoveEvent 183 192 0 0 0 0 0\n"
"RenderEvent 183 192 0 0 0 0 0\n"
"MouseMoveEvent 185 193 0 0 0 0 0\n"
"RenderEvent 185 193 0 0 0 0 0\n"
"MouseMoveEvent 186 195 0 0 0 0 0\n"
"RenderEvent 186 195 0 0 0 0 0\n"
"MouseMoveEvent 188 196 0 0 0 0 0\n"
"RenderEvent 188 196 0 0 0 0 0\n"
"MouseMoveEvent 189 197 0 0 0 0 0\n"
"RenderEvent 189 197 0 0 0 0 0\n"
"MouseMoveEvent 190 199 0 0 0 0 0\n"
"RenderEvent 190 199 0 0 0 0 0\n"
"MouseMoveEvent 191 200 0 0 0 0 0\n"
"RenderEvent 191 200 0 0 0 0 0\n"
"MouseMoveEvent 192 202 0 0 0 0 0\n"
"RenderEvent 192 202 0 0 0 0 0\n"
"MouseMoveEvent 193 202 0 0 0 0 0\n"
"RenderEvent 193 202 0 0 0 0 0\n"
"MouseMoveEvent 194 204 0 0 0 0 0\n"
"RenderEvent 194 204 0 0 0 0 0\n"
"MouseMoveEvent 194 205 0 0 0 0 0\n"
"RenderEvent 194 205 0 0 0 0 0\n"
"MouseMoveEvent 195 206 0 0 0 0 0\n"
"RenderEvent 195 206 0 0 0 0 0\n"
"MouseMoveEvent 195 207 0 0 0 0 0\n"
"RenderEvent 195 207 0 0 0 0 0\n"
"MouseMoveEvent 195 209 0 0 0 0 0\n"
"RenderEvent 195 209 0 0 0 0 0\n"
"MouseMoveEvent 195 210 0 0 0 0 0\n"
"RenderEvent 195 210 0 0 0 0 0\n"
"MouseMoveEvent 195 212 0 0 0 0 0\n"
"RenderEvent 195 212 0 0 0 0 0\n"
"MouseMoveEvent 195 213 0 0 0 0 0\n"
"RenderEvent 195 213 0 0 0 0 0\n"
"MouseMoveEvent 195 214 0 0 0 0 0\n"
"RenderEvent 195 214 0 0 0 0 0\n"
"MouseMoveEvent 195 216 0 0 0 0 0\n"
"RenderEvent 195 216 0 0 0 0 0\n"
"MouseMoveEvent 195 217 0 0 0 0 0\n"
"RenderEvent 195 217 0 0 0 0 0\n"
"MouseMoveEvent 194 218 0 0 0 0 0\n"
"RenderEvent 194 218 0 0 0 0 0\n"
"MouseMoveEvent 193 220 0 0 0 0 0\n"
"RenderEvent 193 220 0 0 0 0 0\n"
"MouseMoveEvent 192 223 0 0 0 0 0\n"
"RenderEvent 192 223 0 0 0 0 0\n"
"MouseMoveEvent 192 224 0 0 0 0 0\n"
"RenderEvent 192 224 0 0 0 0 0\n"
"MouseMoveEvent 191 226 0 0 0 0 0\n"
"RenderEvent 191 226 0 0 0 0 0\n"
"MouseMoveEvent 190 228 0 0 0 0 0\n"
"RenderEvent 190 228 0 0 0 0 0\n"
"MouseMoveEvent 190 229 0 0 0 0 0\n"
"RenderEvent 190 229 0 0 0 0 0\n"
"MouseMoveEvent 190 230 0 0 0 0 0\n"
"RenderEvent 190 230 0 0 0 0 0\n"
"MouseMoveEvent 189 230 0 0 0 0 0\n"
"RenderEvent 189 230 0 0 0 0 0\n"
"MouseMoveEvent 188 231 0 0 0 0 0\n"
"RenderEvent 188 231 0 0 0 0 0\n"
"MouseMoveEvent 187 232 0 0 0 0 0\n"
"RenderEvent 187 232 0 0 0 0 0\n"
"MouseMoveEvent 186 232 0 0 0 0 0\n"
"RenderEvent 186 232 0 0 0 0 0\n"
"MouseMoveEvent 185 233 0 0 0 0 0\n"
"RenderEvent 185 233 0 0 0 0 0\n"
"MouseMoveEvent 183 234 0 0 0 0 0\n"
"RenderEvent 183 234 0 0 0 0 0\n"
"MouseMoveEvent 181 234 0 0 0 0 0\n"
"RenderEvent 181 234 0 0 0 0 0\n"
"MouseMoveEvent 180 235 0 0 0 0 0\n"
"RenderEvent 180 235 0 0 0 0 0\n"
"MouseMoveEvent 178 236 0 0 0 0 0\n"
"RenderEvent 178 236 0 0 0 0 0\n"
"MouseMoveEvent 177 236 0 0 0 0 0\n"
"RenderEvent 177 236 0 0 0 0 0\n"
"MouseMoveEvent 176 236 0 0 0 0 0\n"
"RenderEvent 176 236 0 0 0 0 0\n"
"MouseMoveEvent 175 236 0 0 0 0 0\n"
"RenderEvent 175 236 0 0 0 0 0\n"
"MouseMoveEvent 173 236 0 0 0 0 0\n"
"RenderEvent 173 236 0 0 0 0 0\n"
"MouseMoveEvent 172 236 0 0 0 0 0\n"
"RenderEvent 172 236 0 0 0 0 0\n"
"MouseMoveEvent 172 235 0 0 0 0 0\n"
"RenderEvent 172 235 0 0 0 0 0\n"
"MouseMoveEvent 171 235 0 0 0 0 0\n"
"RenderEvent 171 235 0 0 0 0 0\n"
"MouseMoveEvent 170 234 0 0 0 0 0\n"
"RenderEvent 170 234 0 0 0 0 0\n"
"MouseMoveEvent 169 233 0 0 0 0 0\n"
"RenderEvent 169 233 0 0 0 0 0\n"
"MouseMoveEvent 168 232 0 0 0 0 0\n"
"RenderEvent 168 232 0 0 0 0 0\n"
"MouseMoveEvent 167 231 0 0 0 0 0\n"
"RenderEvent 167 231 0 0 0 0 0\n"
"MouseMoveEvent 167 230 0 0 0 0 0\n"
"RenderEvent 167 230 0 0 0 0 0\n"
"MouseMoveEvent 166 229 0 0 0 0 0\n"
"RenderEvent 166 229 0 0 0 0 0\n"
"MouseMoveEvent 165 227 0 0 0 0 0\n"
"RenderEvent 165 227 0 0 0 0 0\n"
"MouseMoveEvent 165 226 0 0 0 0 0\n"
"RenderEvent 165 226 0 0 0 0 0\n"
"MouseMoveEvent 164 225 0 0 0 0 0\n"
"RenderEvent 164 225 0 0 0 0 0\n"
"MouseMoveEvent 164 224 0 0 0 0 0\n"
"RenderEvent 164 224 0 0 0 0 0\n"
"MouseMoveEvent 164 223 0 0 0 0 0\n"
"RenderEvent 164 223 0 0 0 0 0\n"
"MouseMoveEvent 163 222 0 0 0 0 0\n"
"RenderEvent 163 222 0 0 0 0 0\n"
"MouseMoveEvent 163 220 0 0 0 0 0\n"
"RenderEvent 163 220 0 0 0 0 0\n"
"MouseMoveEvent 163 219 0 0 0 0 0\n"
"RenderEvent 163 219 0 0 0 0 0\n"
"MouseMoveEvent 162 217 0 0 0 0 0\n"
"RenderEvent 162 217 0 0 0 0 0\n"
"MouseMoveEvent 162 216 0 0 0 0 0\n"
"RenderEvent 162 216 0 0 0 0 0\n"
"MouseMoveEvent 162 215 0 0 0 0 0\n"
"RenderEvent 162 215 0 0 0 0 0\n"
"MouseMoveEvent 161 214 0 0 0 0 0\n"
"RenderEvent 161 214 0 0 0 0 0\n"
"MouseMoveEvent 161 213 0 0 0 0 0\n"
"RenderEvent 161 213 0 0 0 0 0\n"
"MouseMoveEvent 161 212 0 0 0 0 0\n"
"RenderEvent 161 212 0 0 0 0 0\n"
"MouseMoveEvent 161 211 0 0 0 0 0\n"
"RenderEvent 161 211 0 0 0 0 0\n"
"MouseMoveEvent 160 210 0 0 0 0 0\n"
"RenderEvent 160 210 0 0 0 0 0\n"
"MouseMoveEvent 160 208 0 0 0 0 0\n"
"RenderEvent 160 208 0 0 0 0 0\n"
"MouseMoveEvent 160 207 0 0 0 0 0\n"
"RenderEvent 160 207 0 0 0 0 0\n"
"MouseMoveEvent 160 206 0 0 0 0 0\n"
"RenderEvent 160 206 0 0 0 0 0\n"
"MouseMoveEvent 160 205 0 0 0 0 0\n"
"RenderEvent 160 205 0 0 0 0 0\n"
"MouseMoveEvent 160 204 0 0 0 0 0\n"
"RenderEvent 160 204 0 0 0 0 0\n"
"MouseMoveEvent 160 203 0 0 0 0 0\n"
"RenderEvent 160 203 0 0 0 0 0\n"
"MouseMoveEvent 160 202 0 0 0 0 0\n"
"RenderEvent 160 202 0 0 0 0 0\n"
"MouseMoveEvent 160 201 0 0 0 0 0\n"
"RenderEvent 160 201 0 0 0 0 0\n"
"MouseMoveEvent 160 200 0 0 0 0 0\n"
"RenderEvent 160 200 0 0 0 0 0\n"
"MouseMoveEvent 160 198 0 0 0 0 0\n"
"RenderEvent 160 198 0 0 0 0 0\n"
"MouseMoveEvent 161 197 0 0 0 0 0\n"
"RenderEvent 161 197 0 0 0 0 0\n"
"MouseMoveEvent 161 196 0 0 0 0 0\n"
"RenderEvent 161 196 0 0 0 0 0\n"
"MouseMoveEvent 161 195 0 0 0 0 0\n"
"RenderEvent 161 195 0 0 0 0 0\n"
"MouseMoveEvent 161 194 0 0 0 0 0\n"
"RenderEvent 161 194 0 0 0 0 0\n"
"MouseMoveEvent 161 193 0 0 0 0 0\n"
"RenderEvent 161 193 0 0 0 0 0\n"
"MouseMoveEvent 161 192 0 0 0 0 0\n"
"RenderEvent 161 192 0 0 0 0 0\n"
"MiddleButtonReleaseEvent 161 192 0 0 0 0 0\n"
"EndInteractionEvent 161 192 0 0 0 0 0\n"
"MouseMoveEvent 161 192 0 0 0 0 0\n"
"MouseMoveEvent 161 191 0 0 0 0 0\n"
"MouseMoveEvent 162 190 0 0 0 0 0\n"
"MouseMoveEvent 163 191 0 0 0 0 0\n"
"MouseMoveEvent 165 192 0 0 0 0 0\n"
"MouseMoveEvent 166 192 0 0 0 0 0\n"
"MouseMoveEvent 167 194 0 0 0 0 0\n"
"MouseMoveEvent 169 195 0 0 0 0 0\n"
"MouseMoveEvent 170 196 0 0 0 0 0\n"
"MouseMoveEvent 171 196 0 0 0 0 0\n"
"MouseMoveEvent 171 197 0 0 0 0 0\n"
"MouseMoveEvent 171 199 0 0 0 0 0\n"
"MouseMoveEvent 172 199 0 0 0 0 0\n"
"RightButtonPressEvent 172 199 0 0 0 0 0\n"
"StartInteractionEvent 172 199 0 0 0 0 0\n"
"MouseMoveEvent 172 200 0 0 0 0 0\n"
"RenderEvent 172 200 0 0 0 0 0\n"
"MouseMoveEvent 173 201 0 0 0 0 0\n"
"RenderEvent 173 201 0 0 0 0 0\n"
"MouseMoveEvent 174 203 0 0 0 0 0\n"
"RenderEvent 174 203 0 0 0 0 0\n"
"MouseMoveEvent 174 204 0 0 0 0 0\n"
"RenderEvent 174 204 0 0 0 0 0\n"
"MouseMoveEvent 174 205 0 0 0 0 0\n"
"RenderEvent 174 205 0 0 0 0 0\n"
"MouseMoveEvent 174 206 0 0 0 0 0\n"
"RenderEvent 174 206 0 0 0 0 0\n"
"MouseMoveEvent 174 208 0 0 0 0 0\n"
"RenderEvent 174 208 0 0 0 0 0\n"
"MouseMoveEvent 175 209 0 0 0 0 0\n"
"RenderEvent 175 209 0 0 0 0 0\n"
"MouseMoveEvent 176 210 0 0 0 0 0\n"
"RenderEvent 176 210 0 0 0 0 0\n"
"MouseMoveEvent 176 211 0 0 0 0 0\n"
"RenderEvent 176 211 0 0 0 0 0\n"
"MouseMoveEvent 177 212 0 0 0 0 0\n"
"RenderEvent 177 212 0 0 0 0 0\n"
"MouseMoveEvent 178 214 0 0 0 0 0\n"
"RenderEvent 178 214 0 0 0 0 0\n"
"MouseMoveEvent 179 214 0 0 0 0 0\n"
"RenderEvent 179 214 0 0 0 0 0\n"
"MouseMoveEvent 179 215 0 0 0 0 0\n"
"RenderEvent 179 215 0 0 0 0 0\n"
"MouseMoveEvent 180 216 0 0 0 0 0\n"
"RenderEvent 180 216 0 0 0 0 0\n"
"MouseMoveEvent 180 217 0 0 0 0 0\n"
"RenderEvent 180 217 0 0 0 0 0\n"
"MouseMoveEvent 181 218 0 0 0 0 0\n"
"RenderEvent 181 218 0 0 0 0 0\n"
"MouseMoveEvent 182 219 0 0 0 0 0\n"
"RenderEvent 182 219 0 0 0 0 0\n"
"MouseMoveEvent 182 220 0 0 0 0 0\n"
"RenderEvent 182 220 0 0 0 0 0\n"
"MouseMoveEvent 183 221 0 0 0 0 0\n"
"RenderEvent 183 221 0 0 0 0 0\n"
"MouseMoveEvent 184 222 0 0 0 0 0\n"
"RenderEvent 184 222 0 0 0 0 0\n"
"MouseMoveEvent 184 224 0 0 0 0 0\n"
"RenderEvent 184 224 0 0 0 0 0\n"
"MouseMoveEvent 186 225 0 0 0 0 0\n"
"RenderEvent 186 225 0 0 0 0 0\n"
"MouseMoveEvent 186 226 0 0 0 0 0\n"
"RenderEvent 186 226 0 0 0 0 0\n"
"MouseMoveEvent 186 227 0 0 0 0 0\n"
"RenderEvent 186 227 0 0 0 0 0\n"
"MouseMoveEvent 187 228 0 0 0 0 0\n"
"RenderEvent 187 228 0 0 0 0 0\n"
"MouseMoveEvent 187 229 0 0 0 0 0\n"
"RenderEvent 187 229 0 0 0 0 0\n"
"MouseMoveEvent 188 230 0 0 0 0 0\n"
"RenderEvent 188 230 0 0 0 0 0\n"
"MouseMoveEvent 189 231 0 0 0 0 0\n"
"RenderEvent 189 231 0 0 0 0 0\n"
"MouseMoveEvent 189 232 0 0 0 0 0\n"
"RenderEvent 189 232 0 0 0 0 0\n"
"MouseMoveEvent 190 233 0 0 0 0 0\n"
"RenderEvent 190 233 0 0 0 0 0\n"
"MouseMoveEvent 190 234 0 0 0 0 0\n"
"RenderEvent 190 234 0 0 0 0 0\n"
"MouseMoveEvent 190 235 0 0 0 0 0\n"
"RenderEvent 190 235 0 0 0 0 0\n"
"MouseMoveEvent 190 237 0 0 0 0 0\n"
"RenderEvent 190 237 0 0 0 0 0\n"
"MouseMoveEvent 190 238 0 0 0 0 0\n"
"RenderEvent 190 238 0 0 0 0 0\n"
"MouseMoveEvent 191 239 0 0 0 0 0\n"
"RenderEvent 191 239 0 0 0 0 0\n"
"MouseMoveEvent 191 240 0 0 0 0 0\n"
"RenderEvent 191 240 0 0 0 0 0\n"
"MouseMoveEvent 191 241 0 0 0 0 0\n"
"RenderEvent 191 241 0 0 0 0 0\n"
"MouseMoveEvent 192 243 0 0 0 0 0\n"
"RenderEvent 192 243 0 0 0 0 0\n"
"MouseMoveEvent 192 244 0 0 0 0 0\n"
"RenderEvent 192 244 0 0 0 0 0\n"
"MouseMoveEvent 190 244 0 0 0 0 0\n"
"RenderEvent 190 244 0 0 0 0 0\n"
"MouseMoveEvent 189 242 0 0 0 0 0\n"
"RenderEvent 189 242 0 0 0 0 0\n"
"MouseMoveEvent 188 242 0 0 0 0 0\n"
"RenderEvent 188 242 0 0 0 0 0\n"
"MouseMoveEvent 187 241 0 0 0 0 0\n"
"RenderEvent 187 241 0 0 0 0 0\n"
"MouseMoveEvent 186 240 0 0 0 0 0\n"
"RenderEvent 186 240 0 0 0 0 0\n"
"MouseMoveEvent 186 239 0 0 0 0 0\n"
"RenderEvent 186 239 0 0 0 0 0\n"
"MouseMoveEvent 185 238 0 0 0 0 0\n"
"RenderEvent 185 238 0 0 0 0 0\n"
"MouseMoveEvent 184 236 0 0 0 0 0\n"
"RenderEvent 184 236 0 0 0 0 0\n"
"MouseMoveEvent 183 235 0 0 0 0 0\n"
"RenderEvent 183 235 0 0 0 0 0\n"
"MouseMoveEvent 183 234 0 0 0 0 0\n"
"RenderEvent 183 234 0 0 0 0 0\n"
"MouseMoveEvent 182 233 0 0 0 0 0\n"
"RenderEvent 182 233 0 0 0 0 0\n"
"MouseMoveEvent 181 233 0 0 0 0 0\n"
"RenderEvent 181 233 0 0 0 0 0\n"
"MouseMoveEvent 181 231 0 0 0 0 0\n"
"RenderEvent 181 231 0 0 0 0 0\n"
"MouseMoveEvent 180 231 0 0 0 0 0\n"
"RenderEvent 180 231 0 0 0 0 0\n"
"MouseMoveEvent 179 230 0 0 0 0 0\n"
"RenderEvent 179 230 0 0 0 0 0\n"
"MouseMoveEvent 178 229 0 0 0 0 0\n"
"RenderEvent 178 229 0 0 0 0 0\n"
"MouseMoveEvent 177 228 0 0 0 0 0\n"
"RenderEvent 177 228 0 0 0 0 0\n"
"MouseMoveEvent 176 228 0 0 0 0 0\n"
"RenderEvent 176 228 0 0 0 0 0\n"
"MouseMoveEvent 176 227 0 0 0 0 0\n"
"RenderEvent 176 227 0 0 0 0 0\n"
"MouseMoveEvent 175 226 0 0 0 0 0\n"
"RenderEvent 175 226 0 0 0 0 0\n"
"MouseMoveEvent 174 226 0 0 0 0 0\n"
"RenderEvent 174 226 0 0 0 0 0\n"
"MouseMoveEvent 174 225 0 0 0 0 0\n"
"RenderEvent 174 225 0 0 0 0 0\n"
"MouseMoveEvent 172 223 0 0 0 0 0\n"
"RenderEvent 172 223 0 0 0 0 0\n"
"MouseMoveEvent 172 222 0 0 0 0 0\n"
"RenderEvent 172 222 0 0 0 0 0\n"
"MouseMoveEvent 171 222 0 0 0 0 0\n"
"RenderEvent 171 222 0 0 0 0 0\n"
"MouseMoveEvent 170 221 0 0 0 0 0\n"
"RenderEvent 170 221 0 0 0 0 0\n"
"MouseMoveEvent 170 220 0 0 0 0 0\n"
"RenderEvent 170 220 0 0 0 0 0\n"
"MouseMoveEvent 169 219 0 0 0 0 0\n"
"RenderEvent 169 219 0 0 0 0 0\n"
"MouseMoveEvent 168 218 0 0 0 0 0\n"
"RenderEvent 168 218 0 0 0 0 0\n"
"MouseMoveEvent 166 216 0 0 0 0 0\n"
"RenderEvent 166 216 0 0 0 0 0\n"
"MouseMoveEvent 165 215 0 0 0 0 0\n"
"RenderEvent 165 215 0 0 0 0 0\n"
"MouseMoveEvent 165 214 0 0 0 0 0\n"
"RenderEvent 165 214 0 0 0 0 0\n"
"MouseMoveEvent 164 213 0 0 0 0 0\n"
"RenderEvent 164 213 0 0 0 0 0\n"
"MouseMoveEvent 163 212 0 0 0 0 0\n"
"RenderEvent 163 212 0 0 0 0 0\n"
"MouseMoveEvent 162 210 0 0 0 0 0\n"
"RenderEvent 162 210 0 0 0 0 0\n"
"MouseMoveEvent 162 209 0 0 0 0 0\n"
"RenderEvent 162 209 0 0 0 0 0\n"
"MouseMoveEvent 161 208 0 0 0 0 0\n"
"RenderEvent 161 208 0 0 0 0 0\n"
"MouseMoveEvent 160 208 0 0 0 0 0\n"
"RenderEvent 160 208 0 0 0 0 0\n"
"MouseMoveEvent 160 207 0 0 0 0 0\n"
"RenderEvent 160 207 0 0 0 0 0\n"
"MouseMoveEvent 159 206 0 0 0 0 0\n"
"RenderEvent 159 206 0 0 0 0 0\n"
"MouseMoveEvent 158 205 0 0 0 0 0\n"
"RenderEvent 158 205 0 0 0 0 0\n"
"MouseMoveEvent 158 204 0 0 0 0 0\n"
"RenderEvent 158 204 0 0 0 0 0\n"
"MouseMoveEvent 157 203 0 0 0 0 0\n"
"RenderEvent 157 203 0 0 0 0 0\n"
"MouseMoveEvent 156 202 0 0 0 0 0\n"
"RenderEvent 156 202 0 0 0 0 0\n"
"MouseMoveEvent 156 201 0 0 0 0 0\n"
"RenderEvent 156 201 0 0 0 0 0\n"
"MouseMoveEvent 155 199 0 0 0 0 0\n"
"RenderEvent 155 199 0 0 0 0 0\n"
"MouseMoveEvent 154 198 0 0 0 0 0\n"
"RenderEvent 154 198 0 0 0 0 0\n"
"MouseMoveEvent 153 197 0 0 0 0 0\n"
"RenderEvent 153 197 0 0 0 0 0\n"
"MouseMoveEvent 152 196 0 0 0 0 0\n"
"RenderEvent 152 196 0 0 0 0 0\n"
"MouseMoveEvent 152 195 0 0 0 0 0\n"
"RenderEvent 152 195 0 0 0 0 0\n"
"MouseMoveEvent 151 194 0 0 0 0 0\n"
"RenderEvent 151 194 0 0 0 0 0\n"
"MouseMoveEvent 150 193 0 0 0 0 0\n"
"RenderEvent 150 193 0 0 0 0 0\n"
"MouseMoveEvent 150 191 0 0 0 0 0\n"
"RenderEvent 150 191 0 0 0 0 0\n"
"MouseMoveEvent 149 191 0 0 0 0 0\n"
"RenderEvent 149 191 0 0 0 0 0\n"
"MouseMoveEvent 149 190 0 0 0 0 0\n"
"RenderEvent 149 190 0 0 0 0 0\n"
"MouseMoveEvent 148 188 0 0 0 0 0\n"
"RenderEvent 148 188 0 0 0 0 0\n"
"MouseMoveEvent 147 188 0 0 0 0 0\n"
"RenderEvent 147 188 0 0 0 0 0\n"
"MouseMoveEvent 147 187 0 0 0 0 0\n"
"RenderEvent 147 187 0 0 0 0 0\n"
"MouseMoveEvent 147 186 0 0 0 0 0\n"
"RenderEvent 147 186 0 0 0 0 0\n"
"MouseMoveEvent 146 186 0 0 0 0 0\n"
"RenderEvent 146 186 0 0 0 0 0\n"
"MouseMoveEvent 145 185 0 0 0 0 0\n"
"RenderEvent 145 185 0 0 0 0 0\n"
"MouseMoveEvent 145 184 0 0 0 0 0\n"
"RenderEvent 145 184 0 0 0 0 0\n"
"MouseMoveEvent 144 183 0 0 0 0 0\n"
"RenderEvent 144 183 0 0 0 0 0\n"
"MouseMoveEvent 144 182 0 0 0 0 0\n"
"RenderEvent 144 182 0 0 0 0 0\n"
"MouseMoveEvent 143 182 0 0 0 0 0\n"
"RenderEvent 143 182 0 0 0 0 0\n"
"MouseMoveEvent 142 180 0 0 0 0 0\n"
"RenderEvent 142 180 0 0 0 0 0\n"
"MouseMoveEvent 142 179 0 0 0 0 0\n"
"RenderEvent 142 179 0 0 0 0 0\n"
"MouseMoveEvent 141 178 0 0 0 0 0\n"
"RenderEvent 141 178 0 0 0 0 0\n"
"MouseMoveEvent 140 177 0 0 0 0 0\n"
"RenderEvent 140 177 0 0 0 0 0\n"
"MouseMoveEvent 140 176 0 0 0 0 0\n"
"RenderEvent 140 176 0 0 0 0 0\n"
"MouseMoveEvent 139 176 0 0 0 0 0\n"
"RenderEvent 139 176 0 0 0 0 0\n"
"MouseMoveEvent 139 175 0 0 0 0 0\n"
"RenderEvent 139 175 0 0 0 0 0\n"
"MouseMoveEvent 138 174 0 0 0 0 0\n"
"RenderEvent 138 174 0 0 0 0 0\n"
"MouseMoveEvent 137 173 0 0 0 0 0\n"
"RenderEvent 137 173 0 0 0 0 0\n"
"MouseMoveEvent 137 171 0 0 0 0 0\n"
"RenderEvent 137 171 0 0 0 0 0\n"
"MouseMoveEvent 136 171 0 0 0 0 0\n"
"RenderEvent 136 171 0 0 0 0 0\n"
"MouseMoveEvent 135 170 0 0 0 0 0\n"
"RenderEvent 135 170 0 0 0 0 0\n"
"MouseMoveEvent 135 168 0 0 0 0 0\n"
"RenderEvent 135 168 0 0 0 0 0\n"
"MouseMoveEvent 133 167 0 0 0 0 0\n"
"RenderEvent 133 167 0 0 0 0 0\n"
"MouseMoveEvent 133 165 0 0 0 0 0\n"
"RenderEvent 133 165 0 0 0 0 0\n"
"MouseMoveEvent 131 163 0 0 0 0 0\n"
"RenderEvent 131 163 0 0 0 0 0\n"
"MouseMoveEvent 130 162 0 0 0 0 0\n"
"RenderEvent 130 162 0 0 0 0 0\n"
"MouseMoveEvent 129 160 0 0 0 0 0\n"
"RenderEvent 129 160 0 0 0 0 0\n"
"MouseMoveEvent 128 159 0 0 0 0 0\n"
"RenderEvent 128 159 0 0 0 0 0\n"
"MouseMoveEvent 128 158 0 0 0 0 0\n"
"RenderEvent 128 158 0 0 0 0 0\n"
"MouseMoveEvent 127 157 0 0 0 0 0\n"
"RenderEvent 127 157 0 0 0 0 0\n"
"MouseMoveEvent 127 156 0 0 0 0 0\n"
"RenderEvent 127 156 0 0 0 0 0\n"
"MouseMoveEvent 126 155 0 0 0 0 0\n"
"RenderEvent 126 155 0 0 0 0 0\n"
"RightButtonReleaseEvent 126 155 0 0 0 0 0\n"
"EndInteractionEvent 126 155 0 0 0 0 0\n"
"MouseMoveEvent 126 155 0 0 0 0 0\n"
"MouseMoveEvent 127 155 0 0 0 0 0\n"
"MouseMoveEvent 127 156 0 0 0 0 0\n"
"MouseMoveEvent 128 156 0 0 0 0 0\n"
"MouseMoveEvent 128 157 0 0 0 0 0\n"
"MouseMoveEvent 130 158 0 0 0 0 0\n"
"MouseMoveEvent 131 159 0 0 0 0 0\n"
"MouseMoveEvent 132 159 0 0 0 0 0\n"
"MouseMoveEvent 133 160 0 0 0 0 0\n"
"MouseWheelForwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseWheelForwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseWheelBackwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseWheelBackwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseWheelBackwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseWheelBackwardEvent 141 132 0 0 0 0 0\n"
"StartInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"EndInteractionEvent 141 132 0 0 0 0 0\n"
"RenderEvent 141 132 0 0 0 0 0\n"
"MouseMoveEvent 133 161 0 0 0 0 0\n"
"MouseWheelForwardEvent 142 133 0 0 0 0 0\n"
"StartInteractionEvent 142 133 0 0 0 0 0\n"
"RenderEvent 142 133 0 0 0 0 0\n"
"EndInteractionEvent 142 133 0 0 0 0 0\n"
"RenderEvent 142 133 0 0 0 0 0\n"
"MouseMoveEvent 134 161 0 0 0 0 0\n"
"MouseWheelForwardEvent 142 133 0 0 0 0 0\n"
"StartInteractionEvent 142 133 0 0 0 0 0\n"
"RenderEvent 142 133 0 0 0 0 0\n"
"EndInteractionEvent 142 133 0 0 0 0 0\n"
"RenderEvent 142 133 0 0 0 0 0\n"
"MouseMoveEvent 134 163 0 0 0 0 0\n"
"MouseMoveEvent 136 163 0 0 0 0 0\n"
"MouseMoveEvent 136 165 0 0 0 0 0\n"
"MouseMoveEvent 138 166 0 0 0 0 0\n"
"MouseMoveEvent 139 168 0 0 0 0 0\n"
"MouseMoveEvent 142 172 0 0 0 0 0\n"
"MouseMoveEvent 145 178 0 0 0 0 0\n"
"MouseMoveEvent 148 184 0 0 0 0 0\n"
"MouseMoveEvent 150 188 0 0 0 0 0\n"
"MouseMoveEvent 153 195 0 0 0 0 0\n"
"MouseMoveEvent 155 201 0 0 0 0 0\n"
"MouseMoveEvent 158 208 0 0 0 0 0\n"
"MouseMoveEvent 161 215 0 0 0 0 0\n"
"MouseMoveEvent 166 221 0 0 0 0 0\n"
"MouseMoveEvent 171 228 0 0 0 0 0\n"
"MouseMoveEvent 176 232 0 0 0 0 0\n"
"MouseMoveEvent 182 238 0 0 0 0 0\n"
"MouseMoveEvent 188 242 0 0 0 0 0\n"
"MouseMoveEvent 193 245 0 0 0 0 0\n"
"MouseMoveEvent 196 248 0 0 0 0 0\n"
"MouseMoveEvent 200 251 0 0 0 0 0\n"
"MouseMoveEvent 203 254 0 0 0 0 0\n"
"MouseMoveEvent 206 257 0 0 0 0 0\n"
"MouseMoveEvent 207 260 0 0 0 0 0\n"
"MouseMoveEvent 210 262 0 0 0 0 0\n"
"MouseMoveEvent 212 266 0 0 0 0 0\n"
"MouseMoveEvent 215 269 0 0 0 0 0\n"
"MouseMoveEvent 218 274 0 0 0 0 0\n"
"MouseMoveEvent 221 277 0 0 0 0 0\n"
"MouseMoveEvent 226 280 0 0 0 0 0\n"
"MouseMoveEvent 229 284 0 0 0 0 0\n"
"MouseMoveEvent 233 286 0 0 0 0 0\n"
"MouseMoveEvent 236 289 0 0 0 0 0\n"
"MouseMoveEvent 240 291 0 0 0 0 0\n"
"MouseMoveEvent 242 293 0 0 0 0 0\n"
"MouseMoveEvent 245 295 0 0 0 0 0\n"
"MouseMoveEvent 248 297 0 0 0 0 0\n"
"MouseMoveEvent 251 299 0 0 0 0 0\n"
"LeaveEvent 251 299 0 0 0 0 0\n"
"ExitEvent 251 299 0 0 0 0 0\n"
;

//#define RECORD

int TestRenderView(int, char*[])
{
  VTK_CREATE(vtkAnnotationLink, link);
  VTK_CREATE(TestRenderViewUpdater, updater);

  VTK_CREATE(vtkSphereSource, sphere);
  VTK_CREATE(vtkCubeSource, cube);
  cube->SetCenter(2, 0, 0);

  VTK_CREATE(vtkTransformFilter, transform);
  VTK_CREATE(vtkTransform, trans);
  trans->Translate(0, 2, 0);
  transform->SetTransform(trans);
  transform->SetInputConnection(sphere->GetOutputPort());

  // Render view 1
  VTK_CREATE(vtkRenderView, view);
  view->DisplayHoverTextOff();
  view->GetRenderWindow()->SetMultiSamples(0);
  updater->AddView(view);

  // Sphere 1
  VTK_CREATE(vtkRenderedSurfaceRepresentation, sphereRep1);
  sphereRep1->SetInputConnection(sphere->GetOutputPort());
  sphereRep1->SetAnnotationLink(link);
  view->AddRepresentation(sphereRep1);
  view->Update();

  // Cube 1
  VTK_CREATE(vtkRenderedSurfaceRepresentation, cubeRep1);
  cubeRep1->SetInputConnection(cube->GetOutputPort());
  view->AddRepresentation(cubeRep1);
  view->Update();

  view->ResetCamera();
  view->GetRenderer()->GradientBackgroundOff();

  // record events
  VTK_CREATE(vtkInteractorEventRecorder, recorder);
  recorder->SetInteractor(view->GetInteractor());
#ifdef RECORD
  recorder->SetFileName("record.log");
  recorder->SetEnabled(true);
  recorder->Record();
#else
  recorder->ReadFromInputStringOn();
  recorder->SetInputString(RenderViewEventLog);
#endif

  // interact with data
  // render the image
  //
  view->GetInteractor()->Initialize();
#ifdef RECORD
#else
  recorder->Play();

  // Remove the observers so we can go interactive. Without this the "-I"
  // testing option fails.
  recorder->Off();
#endif
  view->GetInteractor()->Start();

  return EXIT_SUCCESS;
}
