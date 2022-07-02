import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ReportsclientComponent } from './reportsclient.component';

describe('ReportsclientComponent', () => {
  let component: ReportsclientComponent;
  let fixture: ComponentFixture<ReportsclientComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ ReportsclientComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(ReportsclientComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
