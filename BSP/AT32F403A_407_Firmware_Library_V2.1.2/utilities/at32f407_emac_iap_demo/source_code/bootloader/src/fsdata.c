/**
  **************************************************************************
  * @file     fsdata.c
  * @version  v2.1.2
  * @date     2022-08-16
  * @brief    fsdata
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f403a_407_board.h"
#include "fsdata.h"
#include "stdio.h"

static const char data_index_html[] = {
	0x2f,0x69,0x6e,0x64,0x65,0x78,0x2e,0x68,
	0x74,0x6d,0x6c,0x00,0x48,0x54,0x54,0x50,
	0x2f,0x31,0x2e,0x30,0x20,0x32,0x30,0x30,
	0x20,0x4f,0x4b,0x0d,0x0a,0x53,0x65,0x72,
	0x76,0x65,0x72,0x3a,0x20,0x75,0x49,0x50,
	0x2f,0x30,0x2e,0x39,0x20,0x28,0x68,0x74,
	0x74,0x70,0x3a,0x2f,0x2f,0x64,0x75,0x6e,
	0x6b,0x65,0x6c,0x73,0x2e,0x63,0x6f,0x6d,
	0x2f,0x61,0x64,0x61,0x6d,0x2f,0x75,0x69,
	0x70,0x2f,0x29,0x0d,0x0a,0x43,0x6f,0x6e,
	0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,0x70,
	0x65,0x3a,0x20,0x74,0x65,0x78,0x74,0x2f,
	0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,0x0a,
	0x3c,0x21,0x44,0x4f,0x43,0x54,0x59,0x50,
	0x45,0x20,0x48,0x54,0x4d,0x4c,0x20,0x50,
	0x55,0x42,0x4c,0x49,0x43,0x20,0x22,0x2d,
	0x2f,0x2f,0x57,0x33,0x43,0x2f,0x44,0x54,
	0x44,0x20,0x48,0x54,0x4d,0x4c,0x20,0x34,
	0x2e,0x30,0x20,0x54,0x72,0x61,0x6e,0x73,
	0x69,0x74,0x69,0x6f,0x6e,0x61,0x6c,0x2f,
	0x2f,0x45,0x4e,0x22,0x3e,0x0d,0x0a,0x3c,
	0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,0x3c,
	0x4d,0x45,0x54,0x41,0x20,0x48,0x54,0x54,
	0x50,0x2d,0x45,0x51,0x55,0x49,0x56,0x20,
	0x3d,0x20,0x22,0x50,0x72,0x61,0x67,0x6d,
	0x61,0x22,0x20,0x43,0x4f,0x4e,0x54,0x45,
	0x4e,0x54,0x3d,0x22,0x6e,0x6f,0x2d,0x63,
	0x61,0x63,0x68,0x65,0x22,0x3e,0x0d,0x0a,
	0x3c,0x74,0x69,0x74,0x6c,0x65,0x3e,0x20,
	0x41,0x54,0x33,0x32,0x46,0x34,0x30,0x37,
	0x20,0x49,0x41,0x50,0x20,0x75,0x73,0x69,
	0x6e,0x67,0x20,0x48,0x54,0x54,0x50,0x20,
	0x3c,0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,
	0x0d,0x0a,0x3c,0x62,0x6f,0x64,0x79,0x3e,
	0x0d,0x0a,0x3c,0x68,0x32,0x3e,0x4c,0x6f,
	0x67,0x69,0x6e,0x3c,0x2f,0x68,0x32,0x3e,
	0x0d,0x0a,0x3c,0x46,0x4f,0x52,0x4d,0x20,
	0x4d,0x45,0x54,0x48,0x4f,0x44,0x3d,0x50,
	0x4f,0x53,0x54,0x20,0x41,0x43,0x54,0x49,
	0x4f,0x4e,0x3d,0x22,0x2f,0x63,0x68,0x65,
	0x63,0x6b,0x6c,0x6f,0x67,0x69,0x6e,0x2e,
	0x63,0x67,0x69,0x22,0x3e,0x0d,0x0a,0x3c,
	0x70,0x3e,0x0d,0x0a,0x3c,0x66,0x6f,0x6e,
	0x74,0x20,0x73,0x69,0x7a,0x65,0x3d,0x22,
	0x32,0x22,0x3e,0x20,0x3c,0x73,0x74,0x72,
	0x6f,0x6e,0x67,0x3e,0x20,0x45,0x6e,0x74,
	0x65,0x72,0x20,0x75,0x73,0x65,0x72,0x20,
	0x49,0x44,0x20,0x61,0x6e,0x64,0x20,0x70,
	0x61,0x73,0x73,0x77,0x6f,0x72,0x64,0x3a,
	0x20,0x3c,0x2f,0x73,0x74,0x72,0x6f,0x6e,
	0x67,0x3e,0x3c,0x2f,0x66,0x6f,0x6e,0x74,
	0x3e,0x0d,0x0a,0x3c,0x42,0x52,0x3e,0x0d,
	0x0a,0x3c,0x73,0x74,0x72,0x6f,0x6e,0x67,
	0x3e,0x20,0x55,0x73,0x65,0x72,0x20,0x49,
	0x44,0x3c,0x2f,0x73,0x74,0x72,0x6f,0x6e,
	0x67,0x3e,0x20,0x3c,0x69,0x6e,0x70,0x75,
	0x74,0x20,0x74,0x79,0x70,0x65,0x3d,0x22,
	0x74,0x65,0x78,0x74,0x22,0x20,0x73,0x69,
	0x7a,0x65,0x3d,0x22,0x32,0x30,0x22,0x20,
	0x6e,0x61,0x6d,0x65,0x3d,0x22,0x75,0x73,
	0x65,0x72,0x6e,0x61,0x6d,0x65,0x22,0x3e,
	0x0d,0x0a,0x3c,0x73,0x74,0x72,0x6f,0x6e,
	0x67,0x3e,0x20,0x50,0x61,0x73,0x73,0x77,
	0x6f,0x72,0x64,0x20,0x3c,0x2f,0x73,0x74,
	0x72,0x6f,0x6e,0x67,0x3e,0x20,0x20,0x3c,
	0x69,0x6e,0x70,0x75,0x74,0x20,0x74,0x79,
	0x70,0x65,0x3d,0x22,0x70,0x61,0x73,0x73,
	0x77,0x6f,0x72,0x64,0x22,0x20,0x73,0x69,
	0x7a,0x65,0x3d,0x22,0x32,0x30,0x22,0x20,
	0x6e,0x61,0x6d,0x65,0x3d,0x22,0x70,0x61,
	0x73,0x73,0x77,0x6f,0x72,0x64,0x22,0x3e,
	0x0d,0x0a,0x3c,0x42,0x52,0x3e,0x0d,0x0a,
	0x3c,0x69,0x6e,0x70,0x75,0x74,0x20,0x74,
	0x79,0x70,0x65,0x3d,0x22,0x73,0x75,0x62,
	0x6d,0x69,0x74,0x22,0x20,0x6e,0x61,0x6d,
	0x65,0x3d,0x22,0x6c,0x6f,0x67,0x69,0x6e,
	0x22,0x20,0x76,0x61,0x6c,0x75,0x65,0x3d,
	0x22,0x4c,0x6f,0x67,0x69,0x6e,0x22,0x3e,
	0x0d,0x0a,0x3c,0x2f,0x70,0x3e,0x0d,0x0a,
	0x0d,0x0a,0x3c,0x2f,0x66,0x6f,0x72,0x6d,
	0x3e,0x0d,0x0a,0x3c,0x2f,0x62,0x6f,0x64,
	0x79,0x3e,0x0d,0x0a,0x3c,0x2f,0x68,0x74,
	0x6d,0x6c,0x3e,0x0d,0x0a,};

static const char data_reset_html[] = {
	0x2f,0x72,0x65,0x73,0x65,0x74,0x2e,0x68,
	0x74,0x6d,0x6c,0x00,0x48,0x54,0x54,0x50,
	0x2f,0x31,0x2e,0x30,0x20,0x32,0x30,0x30,
	0x20,0x4f,0x4b,0x0d,0x0a,0x53,0x65,0x72,
	0x76,0x65,0x72,0x3a,0x20,0x75,0x49,0x50,
	0x2f,0x30,0x2e,0x39,0x20,0x28,0x68,0x74,
	0x74,0x70,0x3a,0x2f,0x2f,0x64,0x75,0x6e,
	0x6b,0x65,0x6c,0x73,0x2e,0x63,0x6f,0x6d,
	0x2f,0x61,0x64,0x61,0x6d,0x2f,0x75,0x69,
	0x70,0x2f,0x29,0x0d,0x0a,0x43,0x6f,0x6e,
	0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,0x70,
	0x65,0x3a,0x20,0x74,0x65,0x78,0x74,0x2f,
	0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,0x0a,
	0x3c,0x21,0x44,0x4f,0x43,0x54,0x59,0x50,
	0x45,0x20,0x48,0x54,0x4d,0x4c,0x20,0x50,
	0x55,0x42,0x4c,0x49,0x43,0x20,0x22,0x2d,
	0x2f,0x2f,0x57,0x33,0x43,0x2f,0x2f,0x44,
	0x54,0x44,0x20,0x48,0x54,0x4d,0x4c,0x20,
	0x34,0x2e,0x30,0x31,0x20,0x54,0x72,0x61,
	0x6e,0x73,0x69,0x74,0x69,0x6f,0x6e,0x61,
	0x6c,0x2f,0x2f,0x45,0x4e,0x22,0x3e,0x0d,
	0x0a,0x3c,0x68,0x74,0x6d,0x6c,0x3e,0x20,
	0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,0x20,
	0x3c,0x68,0x65,0x61,0x64,0x3e,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,
	0x20,0x20,0x20,0x3c,0x6d,0x65,0x74,0x61,
	0x20,0x68,0x74,0x74,0x70,0x2d,0x65,0x71,
	0x75,0x69,0x76,0x3d,0x22,0x63,0x6f,0x6e,
	0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,0x70,
	0x65,0x22,0x20,0x63,0x6f,0x6e,0x74,0x65,
	0x6e,0x74,0x3d,0x22,0x74,0x65,0x78,0x74,
	0x2f,0x68,0x74,0x6d,0x6c,0x3b,0x20,0x63,
	0x68,0x61,0x72,0x73,0x65,0x74,0x3d,0x77,
	0x69,0x6e,0x64,0x6f,0x77,0x73,0x2d,0x31,
	0x32,0x35,0x30,0x22,0x3e,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,0x20,
	0x20,0x20,0x3c,0x74,0x69,0x74,0x6c,0x65,
	0x3e,0x41,0x54,0x33,0x32,0x20,0x49,0x41,
	0x50,0x20,0x75,0x73,0x69,0x6e,0x67,0x20,
	0x48,0x54,0x54,0x50,0x20,0x20,0x20,0x20,
	0x20,0x0d,0x0a,0x20,0x20,0x20,0x20,0x3c,
	0x2f,0x74,0x69,0x74,0x6c,0x65,0x3e,0x20,
	0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,0x20,
	0x3c,0x2f,0x68,0x65,0x61,0x64,0x3e,0x20,
	0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,0x20,
	0x3c,0x62,0x6f,0x64,0x79,0x3e,0x20,0x20,
	0x4d,0x43,0x55,0x20,0x52,0x65,0x73,0x65,
	0x74,0x20,0x44,0x6f,0x6e,0x65,0x20,0x21,
	0x20,0x20,0x20,0x20,0x20,0x20,0x0d,0x0a,
	0x20,0x20,0x3c,0x2f,0x62,0x6f,0x64,0x79,
	0x3e,0x0d,0x0a,0x3c,0x2f,0x68,0x74,0x6d,
  0x6c,0x3e,};

static const char data_upload_html[] = {
	0x2f,0x75,0x70,0x6c,0x6f,0x61,0x64,0x2e,
	0x68,0x74,0x6d,0x6c,0x00,0x48,0x54,0x54,
	0x50,0x2f,0x31,0x2e,0x30,0x20,0x32,0x30,
	0x30,0x20,0x4f,0x4b,0x0d,0x0a,0x53,0x65,
	0x72,0x76,0x65,0x72,0x3a,0x20,0x75,0x49,
	0x50,0x2f,0x30,0x2e,0x39,0x20,0x28,0x68,
	0x74,0x74,0x70,0x3a,0x2f,0x2f,0x64,0x75,
	0x6e,0x6b,0x65,0x6c,0x73,0x2e,0x63,0x6f,
	0x6d,0x2f,0x61,0x64,0x61,0x6d,0x2f,0x75,
	0x69,0x70,0x2f,0x29,0x0d,0x0a,0x43,0x6f,
	0x6e,0x74,0x65,0x6e,0x74,0x2d,0x74,0x79,
	0x70,0x65,0x3a,0x20,0x74,0x65,0x78,0x74,
	0x2f,0x68,0x74,0x6d,0x6c,0x0d,0x0a,0x0d,
	0x0a,0x3c,0x21,0x44,0x4f,0x43,0x54,0x59,
	0x50,0x45,0x20,0x48,0x54,0x4d,0x4c,0x20,
	0x50,0x55,0x42,0x4c,0x49,0x43,0x20,0x22,
	0x2d,0x2f,0x2f,0x57,0x33,0x43,0x2f,0x2f,
	0x44,0x54,0x44,0x20,0x48,0x54,0x4d,0x4c,
	0x20,0x34,0x2e,0x30,0x31,0x20,0x54,0x72,
	0x61,0x6e,0x73,0x69,0x74,0x69,0x6f,0x6e,
	0x61,0x6c,0x2f,0x2f,0x45,0x4e,0x22,0x3e,
	0x0d,0x0a,0x3c,0x68,0x74,0x6d,0x6c,0x3e,
	0x0d,0x0a,0x20,0x20,0x3c,0x68,0x65,0x61,
	0x64,0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x6d,
	0x65,0x74,0x61,0x20,0x68,0x74,0x74,0x70,
	0x2d,0x65,0x71,0x75,0x69,0x76,0x3d,0x22,
	0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x2d,
	0x74,0x79,0x70,0x65,0x22,0x20,0x63,0x6f,
	0x6e,0x74,0x65,0x6e,0x74,0x3d,0x22,0x74,
	0x65,0x78,0x74,0x2f,0x68,0x74,0x6d,0x6c,
	0x3b,0x20,0x63,0x68,0x61,0x72,0x73,0x65,
	0x74,0x3d,0x77,0x69,0x6e,0x64,0x6f,0x77,
	0x73,0x2d,0x31,0x32,0x35,0x30,0x22,0x3e,
	0x0d,0x0a,0x20,0x20,0x3c,0x74,0x69,0x74,
	0x6c,0x65,0x3e,0x41,0x54,0x33,0x32,0x46,
	0x34,0x30,0x37,0x20,0x49,0x41,0x50,0x20,
	0x75,0x73,0x69,0x6e,0x67,0x20,0x48,0x54,
	0x54,0x50,0x3c,0x2f,0x74,0x69,0x74,0x6c,
	0x65,0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x2f,
	0x68,0x65,0x61,0x64,0x3e,0x0d,0x0a,0x20,
	0x20,0x3c,0x62,0x6f,0x64,0x79,0x3e,0x0d,
	0x0a,0x20,0x20,0x20,0x20,0x3c,0x66,0x6f,
	0x72,0x6d,0x20,0x61,0x63,0x74,0x69,0x6f,
	0x6e,0x20,0x3d,0x22,0x2f,0x75,0x70,0x6c,
	0x6f,0x61,0x64,0x2e,0x63,0x67,0x69,0x22,
	0x20,0x65,0x6e,0x63,0x74,0x79,0x70,0x65,
	0x3d,0x22,0x6d,0x75,0x6c,0x74,0x69,0x70,
	0x61,0x72,0x74,0x2f,0x66,0x6f,0x72,0x6d,
	0x2d,0x64,0x61,0x74,0x61,0x22,0x20,0x6d,
	0x65,0x74,0x68,0x6f,0x64,0x3d,0x22,0x70,
	0x6f,0x73,0x74,0x22,0x3e,0x0d,0x0a,0x20,
	0x20,0x3c,0x70,0x3e,0x50,0x6c,0x65,0x61,
	0x73,0x65,0x20,0x73,0x70,0x65,0x63,0x69,
	0x66,0x79,0x20,0x61,0x20,0x62,0x69,0x6e,
	0x61,0x72,0x79,0x20,0x66,0x69,0x6c,0x65,
	0x20,0x74,0x6f,0x20,0x75,0x70,0x6c,0x6f,
	0x61,0x64,0x20,0x69,0x6e,0x74,0x6f,0x20,
	0x41,0x54,0x33,0x32,0x46,0x34,0x30,0x37,
	0x20,0x66,0x6c,0x61,0x73,0x68,0x3a,0x0d,
	0x0a,0x20,0x20,0x20,0x20,0x3c,0x62,0x72,
	0x3e,0x0d,0x0a,0x20,0x20,0x20,0x20,0x3c,
	0x69,0x6e,0x70,0x75,0x74,0x20,0x74,0x79,
	0x70,0x65,0x3d,0x22,0x66,0x69,0x6c,0x65,
	0x22,0x20,0x6e,0x61,0x6d,0x65,0x3d,0x22,
	0x64,0x61,0x74,0x61,0x66,0x69,0x6c,0x65,
	0x22,0x20,0x73,0x69,0x7a,0x65,0x3d,0x22,
	0x34,0x30,0x22,0x3e,0x0d,0x0a,0x20,0x20,
	0x3c,0x2f,0x70,0x3e,0x0d,0x0a,0x20,0x20,
	0x3c,0x64,0x69,0x76,0x3e,0x0d,0x0a,0x20,
	0x20,0x20,0x20,0x3c,0x69,0x6e,0x70,0x75,
	0x74,0x20,0x74,0x79,0x70,0x65,0x3d,0x22,
	0x73,0x75,0x62,0x6d,0x69,0x74,0x22,0x20,
	0x76,0x61,0x6c,0x75,0x65,0x3d,0x22,0x55,
	0x70,0x6c,0x6f,0x61,0x64,0x22,0x3e,0x0d,
	0x0a,0x20,0x20,0x3c,0x2f,0x64,0x69,0x76,
	0x3e,0x0d,0x0a,0x3c,0x2f,0x66,0x6f,0x72,
	0x6d,0x3e,0x0d,0x0a,0x20,0x20,0x3c,0x2f,
	0x62,0x6f,0x64,0x79,0x3e,0x0d,0x0a,0x3c,
	0x2f,0x68,0x74,0x6d,0x6c,0x3e,0x0d,0x0a,};

static const char data_uploaddone_html[] = {
	0x2f,0x75,0x70,0x6c,0x6f,0x61,0x64,0x64,
	0x6f,0x6e,0x65,0x2e,0x68,0x74,0x6d,0x6c,
	0x00,0x48,0x54,0x54,0x50,0x2f,0x31,0x2e,
	0x30,0x20,0x32,0x30,0x30,0x20,0x4f,0x4b,
	0x0d,0x0a,0x53,0x65,0x72,0x76,0x65,0x72,
	0x3a,0x20,0x75,0x49,0x50,0x2f,0x30,0x2e,
	0x39,0x20,0x28,0x68,0x74,0x74,0x70,0x3a,
	0x2f,0x2f,0x64,0x75,0x6e,0x6b,0x65,0x6c,
	0x73,0x2e,0x63,0x6f,0x6d,0x2f,0x61,0x64,
	0x61,0x6d,0x2f,0x75,0x69,0x70,0x2f,0x29,
	0x0d,0x0a,0x43,0x6f,0x6e,0x74,0x65,0x6e,
	0x74,0x2d,0x74,0x79,0x70,0x65,0x3a,0x20,
	0x74,0x65,0x78,0x74,0x2f,0x68,0x74,0x6d,
	0x6c,0x0d,0x0a,0x0d,0x0a,0x3c,0x21,0x44,
	0x4f,0x43,0x54,0x59,0x50,0x45,0x20,0x48,
	0x54,0x4d,0x4c,0x20,0x50,0x55,0x42,0x4c,
	0x49,0x43,0x20,0x22,0x2d,0x2f,0x2f,0x57,
	0x33,0x43,0x2f,0x2f,0x44,0x54,0x44,0x20,
	0x48,0x54,0x4d,0x4c,0x20,0x34,0x2e,0x30,
	0x31,0x20,0x54,0x72,0x61,0x6e,0x73,0x69,
	0x74,0x69,0x6f,0x6e,0x61,0x6c,0x2f,0x2f,
	0x45,0x4e,0x22,0x3e,0x0d,0x0a,0x3c,0x68,
	0x74,0x6d,0x6c,0x3e,0x20,0x20,0x20,0x20,
	0x20,0x0d,0x0a,0x20,0x20,0x3c,0x68,0x65,
	0x61,0x64,0x3e,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x0d,0x0a,0x20,0x20,0x20,0x20,
	0x3c,0x6d,0x65,0x74,0x61,0x20,0x68,0x74,
	0x74,0x70,0x2d,0x65,0x71,0x75,0x69,0x76,
	0x3d,0x22,0x63,0x6f,0x6e,0x74,0x65,0x6e,
	0x74,0x2d,0x74,0x79,0x70,0x65,0x22,0x20,
	0x63,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x3d,
	0x22,0x74,0x65,0x78,0x74,0x2f,0x68,0x74,
	0x6d,0x6c,0x3b,0x20,0x63,0x68,0x61,0x72,
	0x73,0x65,0x74,0x3d,0x77,0x69,0x6e,0x64,
	0x6f,0x77,0x73,0x2d,0x31,0x32,0x35,0x30,
	0x22,0x3e,0x20,0x20,0x20,0x20,0x20,0x20,
	0x20,0x0d,0x0a,0x20,0x20,0x20,0x20,0x3c,
	0x74,0x69,0x74,0x6c,0x65,0x3e,0x41,0x54,
	0x33,0x32,0x20,0x49,0x41,0x50,0x20,0x75,
	0x73,0x69,0x6e,0x67,0x20,0x48,0x54,0x54,
	0x50,0x20,0x20,0x20,0x20,0x20,0x0d,0x0a,
	0x20,0x20,0x20,0x20,0x3c,0x2f,0x74,0x69,
	0x74,0x6c,0x65,0x3e,0x20,0x20,0x20,0x20,
	0x20,0x0d,0x0a,0x20,0x20,0x3c,0x2f,0x68,
	0x65,0x61,0x64,0x3e,0x20,0x20,0x20,0x20,
	0x20,0x0d,0x0a,0x20,0x20,0x3c,0x62,0x6f,
	0x64,0x79,0x3e,0x20,0x20,0x46,0x69,0x6c,
	0x65,0x20,0x55,0x70,0x6c,0x6f,0x61,0x64,
	0x20,0x44,0x6f,0x6e,0x65,0x21,0x20,0x20,
	0x20,0x20,0x20,0x20,0x0d,0x0a,0x20,0x20,
	0x20,0x20,0x3c,0x62,0x72,0x3e,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x0d,0x0a,
	0x20,0x20,0x20,0x20,0x3c,0x66,0x6f,0x72,
	0x6d,0x20,0x61,0x63,0x74,0x69,0x6f,0x6e,
	0x20,0x3d,0x22,0x2f,0x72,0x65,0x73,0x65,
	0x74,0x6d,0x63,0x75,0x2e,0x63,0x67,0x69,
	0x22,0x20,0x65,0x6e,0x63,0x74,0x79,0x70,
	0x65,0x3d,0x22,0x74,0x65,0x78,0x74,0x2f,
	0x70,0x6c,0x61,0x69,0x6e,0x22,0x20,0x6d,
	0x65,0x74,0x68,0x6f,0x64,0x3d,0x22,0x67,
	0x65,0x74,0x22,0x3e,0x20,0x20,0x20,0x20,
	0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,
	0x3c,0x69,0x6e,0x70,0x75,0x74,0x20,0x74,
	0x79,0x70,0x65,0x3d,0x22,0x73,0x75,0x62,
	0x6d,0x69,0x74,0x22,0x20,0x76,0x61,0x6c,
	0x75,0x65,0x3d,0x22,0x52,0x65,0x73,0x65,
	0x74,0x20,0x4d,0x43,0x55,0x22,0x3e,0x0d,
	0x0a,0x20,0x20,0x20,0x20,0x3c,0x2f,0x66,
	0x6f,0x72,0x6d,0x3e,0x20,0x20,0x0d,0x0a,
	0x20,0x20,0x3c,0x2f,0x62,0x6f,0x64,0x79,
	0x3e,0x0d,0x0a,0x3c,0x2f,0x68,0x74,0x6d,
  0x6c,0x3e,};

const struct fsdata_file file_index_html[] = {{NULL, data_index_html, data_index_html + 12, sizeof(data_index_html) - 12}};
const struct fsdata_file file_reset_html[] = {{file_index_html, data_reset_html, data_reset_html + 12, sizeof(data_reset_html) - 12}};
const struct fsdata_file file_upload_html[] = {{file_reset_html, data_upload_html, data_upload_html + 13, sizeof(data_upload_html) - 13}};
const struct fsdata_file file_uploaddone_html[] = {{file_upload_html, data_uploaddone_html, data_uploaddone_html + 17, sizeof(data_uploaddone_html) - 17}};

