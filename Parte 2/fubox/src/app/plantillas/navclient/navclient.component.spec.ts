import { ComponentFixture, TestBed } from '@angular/core/testing';

import { NavclientComponent } from './navclient.component';

describe('NavclientComponent', () => {
  let component: NavclientComponent;
  let fixture: ComponentFixture<NavclientComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ NavclientComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(NavclientComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
