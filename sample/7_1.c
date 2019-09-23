bool Dispatch(CROSS cross)
{
    
	for (int r = 0; r < 4; r++)
	{
		vector<FIRSTCARS>firstcars;
		FirstPriviledge(cross, firstcars);//得到当前最高优先级车

		if (cross.LinkedRoadId[r] != -1)
		{
			bool conflict=false;
			int roadid = cross.LinkedRoadId[r];
			int nextroadid = cars[firstcars[r].id].Route[cars[firstcars[r].id].NowRoadIndex + 1];//当前道路最高优先级车辆将进入的道路id
			int n;//nextroadid对应在cross中的顺序索引
			for(int i=0;i<4;i++)
				if (roads[i].RoadId = nextroadid) {
					n = i;
				}

			if (r - n == 2 || r - n == -2);
			else {
				for (int i = 0; i < 4; i++)
				{
					if (i == r || i == n) continue;
					if (cars[firstcars[i].id].Route[cars[firstcars[i].id].NowRoadIndex + 1] == nextroadid)
					{
						if (i - n == 2 || i - n == -2 || i - n == 3 || i - n == -1)
						{
							conflict = true;
							break;
						}
						//是否冲突
					}
				}
			}

			if (conflict)
				continue;
			else //若没有冲突则过马路（若前车为终止状态），需要改变的量 ： road carinfo ， waiting cars，car nowspeed ， car nowroadid， car status
			{
				int flag = 1; //是否真的过了马路
				if (roads[nextroadid].FromId == cross.CrossId)
				{
					//在下一条路的最大速度
					int v2 = (roads[nextroadid].LimitedSpeed <= cars[firstcars[r].id].MaxSpeed ? roads[nextroadid].LimitedSpeed : cars[firstcars[r].id].MaxSpeed);
					int channel = roads[nextroadid].Channel - 1;
					for (int i = roads[nextroadid].Length - 1; i >= 0; i--)
					{					
			 again1:   	int carid = roads[nextroadid].CarInfo[channel][i];
						if (carid != -1 && v2 > firstcars[r].letf_to_run + roads[nextroadid].Length - i - 1) //前面道路有车挡住
						{
							if (cars[carid].Status == Waiting) { flag = 0; break; }//不能过马路
							else
							{
								if (i == roads[nextroadid].Length - 1)//车道满了
								{
									if (channel != 0)
									{
										channel--;
										goto again1;
									}
									else
									{
										flag = 0;
										break;
									}
								}
								roads[nextroadid].CarInfo[channel][i + 1] = firstcars[r].id;
								roads[roadid].CarInfo[firstcars[r].posy][firstcars[r].posx] = -1;
								cars[firstcars[r].id].Status = Stopping;
								cars[firstcars[r].id].NowSpeed = (v2>=cars[roads[nextroadid].CarInfo[channel][i]].NowSpeed? cars[roads[nextroadid].CarInfo[channel][i]].NowSpeed:v2);
								cars[firstcars[r].id].NowRoadIndex++;
								waiting_cars[roadid].up_half--;
								break;

							}
						}
						else
						{
							if (carid == -1 && i == firstcars[r].letf_to_run + roads[nextroadid].Length - v2) //未考虑跑车
							{
								roads[nextroadid].CarInfo[channel][i]= firstcars[r].id;
								roads[roadid].CarInfo[firstcars[r].posy][firstcars[r].posx] = -1;
								cars[firstcars[r].id].Status = Stopping;
								cars[firstcars[r].id].NowSpeed = v2;
								cars[firstcars[r].id].NowRoadIndex++;
								waiting_cars[roadid].up_half--;
								break;
						    }
						}
					}
					if (flag == 1) //真实通过了马路
					{
						AssignAgain(roads[roadid]);
						r--;
						continue;
					}
					continue;

				}
				else
				{
					//在下一条路的最大速度
					int v2 = (roads[nextroadid].LimitedSpeed <= cars[firstcars[r].id].MaxSpeed ? roads[nextroadid].LimitedSpeed : cars[firstcars[r].id].MaxSpeed);
					int channel = roads[nextroadid].Channel ;
					for (int i = 0; i < roads[nextroadid].Length; i++)
					{
			again2:   	int carid = roads[nextroadid].CarInfo[channel][i];
						if (carid != -1 && v2 > firstcars[r].letf_to_run + i) //前面道路有车挡住
						{
							if (cars[carid].Status == Waiting) { flag = 0; break; }//不能过马路
							else
							{
								if (i == 0)//车道满了
								{
									if (channel != roads[nextroadid].Channel*2-1)
									{
										channel++;
										goto again2;
									}
									else
									{
										flag = 0;
										break;
									}
								}
								roads[nextroadid].CarInfo[channel][i - 1] = firstcars[r].id;
								roads[roadid].CarInfo[firstcars[r].posy][firstcars[r].posx] = -1;
								cars[firstcars[r].id].Status = Stopping;
								cars[firstcars[r].id].NowSpeed = (v2 >= cars[roads[nextroadid].CarInfo[channel][i]].NowSpeed ? cars[roads[nextroadid].CarInfo[channel][i]].NowSpeed : v2);
								cars[firstcars[r].id].NowRoadIndex++;
								waiting_cars[roadid].down_half--;
								break;

							}
						}
						else
						{
							if (carid == -1 && i == v2- firstcars[r].letf_to_run-1) //未考虑跑车
							{
								roads[nextroadid].CarInfo[channel][i] = firstcars[r].id;
								roads[roadid].CarInfo[firstcars[r].posy][firstcars[r].posx] = -1;
								cars[firstcars[r].id].Status = Stopping;
								cars[firstcars[r].id].NowSpeed = v2;
								cars[firstcars[r].id].NowRoadIndex++;
								waiting_cars[roadid].down_half--;
								break;
							}
						}
					}

					if (flag == 1) //真实通过了马路
					{
						AssignAgain(roads[roadid],2);
						r--;
						continue;
					}
					continue;
				}
			}
		}
	}
}